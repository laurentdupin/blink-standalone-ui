#ifndef STANDALONE_RENDERER_STUBS_NET_URL_REQUEST_REDIRECT_INFO_H_
#define STANDALONE_RENDERER_STUBS_NET_URL_REQUEST_REDIRECT_INFO_H_

#include <string>

#include "net/cookies/site_for_cookies.h"
#include "net/url_request/referrer_policy.h"
#include "url/gurl.h"

namespace net {

struct RedirectInfo {
  GURL new_url;
  std::string new_method;
  std::string new_referrer;
  ReferrerPolicy new_referrer_policy = ReferrerPolicy::CLEAR_ON_TRANSITION_FROM_SECURE_TO_INSECURE;
  SiteForCookies new_site_for_cookies;
};

}  // namespace net

#endif  // STANDALONE_RENDERER_STUBS_NET_URL_REQUEST_REDIRECT_INFO_H_
