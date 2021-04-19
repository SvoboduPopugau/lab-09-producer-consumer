//
// Created by vladislav on 12.04.2021.
//

#include <HtmlParser.hpp>

std::string ModifyToUrl(EndPoint& ep) {
  if (ep.target.substr(0, 4) == "http") {
    return ep.target;
  }
  if (ep.target.substr(0, 2) == "//") {
    return ep.protocol + ':' + ep.target;
  } else if (ep.target.substr(0, 1) == "/") {
    return ep.protocol + "://" + ep.domain + ep.target;
  }
  return "Unknown url";
}

bool IsUrl(const char* link) {
  if (link[0] == '#')  // Ignore tags
    return false;

  if (link[0] == '\0')  // Ignore empty urls
    return false;

  if (link[0] == '/' || link[0] == '?') {  // Relative page or request
    if (link[1] == '\0')                   // Ignore self-links
      return false;
    if (link[0] == '#')  // Ignore tags
      return false;
    return true;
  }
  return true;
}

static void search_links(GumboNode* node, std::vector<std::string>& v_links) {
  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }
  GumboAttribute* href;
  if (node->v.element.tag == GUMBO_TAG_A &&
      (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
    //    std::cout << href->value << std::endl;
    if (IsUrl(href->value)) v_links.emplace_back(href->value);
  }
  GumboAttribute* src;
  if ((node->v.element.tag == GUMBO_TAG_IMG ||
       node->v.element.tag == GUMBO_TAG_IMAGE) &&
      (src = gumbo_get_attribute(&node->v.element.attributes, "src"))) {
    if ((src->value[0] != '\0') && (IsUrl(src->value)))  // Ignore empty
      v_links.emplace_back(src->value);
  }

  GumboVector* children = &node->v.element.children;
  for (unsigned int i = 0; i < children->length; ++i) {
    search_links(static_cast<GumboNode*>(children->data[i]), v_links);
  }
}

bool IsImage(std::string& link) {
  static const std::vector<std::string> imageExtensions = {
      "apng", "avif", "gif",  "jpg", "jpeg", "jfif", "pjpeg", "pjp",
      "png",  "svg",  "webp", "bmp", "ico",  "cur",  "tif",   "tiff"};

  size_t LastDotPos = link.find_last_of('.');
  if (LastDotPos == std::string::npos) return false;
  std::string end_of_link =
      link.substr(LastDotPos + 1, link.size() - LastDotPos - 1);
  for (auto& x : imageExtensions) {
    if (x == end_of_link) return true;
  }
  return std::any_of(imageExtensions.begin(), imageExtensions.end(),
                     [&](const std::string& s) { return end_of_link == s; });
}

std::vector<EndPoint> HtmlParser::GetLinks(const Page& html_page) {
  std::vector<std::string> links;
  GumboOutput* output = gumbo_parse(html_page.html_text.c_str());
  search_links(output->root, links);
  std::vector<EndPoint> ep_links;
  ep_links.reserve(links.size());
  for (auto& x : links) {
    ep_links.push_back(
        {html_page.protocol, html_page.domain, x, html_page.level + 1});
  }
  return ep_links;
}

std::vector<EndPoint> HtmlParser::GetPng(std::vector<EndPoint>& Links) {
  std::vector<EndPoint> ep_Pnglinks;
  std::vector<EndPoint> ep_Weblinks;
  for (auto& x : Links) {
    if (IsImage(x.target)) {
      ep_Pnglinks.push_back(std::move(x));
    } else {
      ep_Weblinks.push_back(std::move(x));
    }
  }
  Links.clear();
  Links = ep_Weblinks;
  return ep_Pnglinks;
}

void HtmlParser::ParsePage(Page& page, MyQueue<EndPoint>& writeQueue,
                           MyQueue<Url>& findQueue, size_t& depth) {
  std::vector<EndPoint> Links = GetLinks(page);
  std::vector<EndPoint> Images = GetPng(Links);
  if (page.level <= depth)
  {
    for (auto& x : Links) {
      std::string str_url = ModifyToUrl(x);
      if (str_url != "Unknown url") {
        findQueue.Push({str_url, x.level});
        //        std::cout << "Find: " << str_url << std::endl;
      }
    }
  }
  writeQueue.Push(std::move(Images));
}
