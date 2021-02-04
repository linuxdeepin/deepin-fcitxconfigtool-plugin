<<<<<<< HEAD
///*
// * SPDX-FileCopyrightText: 2017-2017 CSSlayer <wengxt@gmail.com>
// *
// * SPDX-License-Identifier: LGPL-2.1-or-later
// *
// */
//#include "i18n.h"
//#include <mutex>
//#include <string>
//#include <unordered_set>
//#include <libintl.h>
//// #include "fcitxutils_export.h"
//// #include "standardpath.h"
=======
/*
 * SPDX-FileCopyrightText: 2017-2017 CSSlayer <wengxt@gmail.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 */
#include "i18n.h"
#include <mutex>
#include <string>
#include <unordered_set>
#include <libintl.h>
>>>>>>> cdc386b... feat: 添加输入法界面完成

//#include <fcitx-utils/utils.h>

//namespace fcitx {

<<<<<<< HEAD
//class GettextManager {
//public:
//    void addDomain(const char *domain, const char *dir = nullptr) {
//        std::lock_guard<std::mutex> lock(mutex_);
//        if (domains_.count(domain)) {
//            return;
//        }
//        // const auto *localedir = StandardPath::fcitxPath("localedir");
//        const auto *localedir = fcitx_utils_get_fcitx_path_with_filename("localedir","fcitx");
//        if (!dir) {
//            dir = localedir;
//        }
//        bindtextdomain(domain, dir);
//        bind_textdomain_codeset(domain, "UTF-8");
//        domains_.insert(domain);
//        // FCITX_DEBUG() << "Add gettext domain " << domain << " at " << dir;
//    }
=======
class GettextManager
{
public:
    void addDomain(const char *domain, const char *dir = nullptr)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (domains_.count(domain)) {
            return;
        }
        const auto *localedir = fcitx_utils_get_fcitx_path_with_filename("localedir", "fcitx");
        if (!dir) {
            dir = localedir;
        }
        bindtextdomain(domain, dir);
        bind_textdomain_codeset(domain, "UTF-8");
        domains_.insert(domain);
        // FCITX_DEBUG() << "Add gettext domain " << domain << " at " << dir;
    }
>>>>>>> cdc386b... feat: 添加输入法界面完成

//private:
//    std::mutex mutex_;
//    std::unordered_set<std::string> domains_;
//};

//static GettextManager gettextManager;

<<<<<<< HEAD
//std::string translate(const std::string &s) {
//    return translate(s.c_str());
//}

//const char *translate(const char *s) { return ::gettext(s); }

//std::string translateCtx(const char *ctx,
//                                           const std::string &s) {
//    return translateCtx(ctx, s.c_str());
//}

//const char *translateCtx(const char *ctx, const char *s) {
//    auto str = stringutils::concat(ctx, "\004", s);
//    const auto *p = str.c_str();
//    const auto *result = ::gettext(str.c_str());
//    if (p == result) {
//        return s;
//    }
//    return result;
//}

//std::string translateDomain(const char *domain,
//                                              const std::string &s) {
//    return translateDomain(domain, s.c_str());
//}

//const char *translateDomain(const char *domain,
//                                              const char *s) {
//    gettextManager.addDomain(domain);
//    return ::dgettext(domain, s);
//}

//std::string
//translateDomainCtx(const char *domain, const char *ctx, const std::string &s) {
//    return translateDomainCtx(domain, ctx, s.c_str());
//}

//const char *
//translateDomainCtx(const char *domain, const char *ctx, const char *s) {
//    gettextManager.addDomain(domain);
//    auto str = stringutils::concat(ctx, "\004", s);
//    const auto *p = str.c_str();
//    const auto *result = ::dgettext(domain, p);
//    if (p == result) {
//        return s;
//    }
//    return result;
//}

//void registerDomain(const char *domain, const char *dir) {
//    gettextManager.addDomain(domain, dir);
//}
//} // namespace fcitx
=======
std::string translate(const std::string &s)
{
    return translate(s.c_str());
}

const char *translate(const char *s)
{
    return ::gettext(s);
}

std::string translateCtx(const char *ctx,
                         const std::string &s)
{
    return translateCtx(ctx, s.c_str());
}

const char *translateCtx(const char *ctx, const char *s)
{
    std::string str = nullptr;
    str.append(ctx);
    str.append("\004");
    str.append(s);
    const auto *p = str.c_str();
    const auto *result = ::gettext(str.c_str());
    if (p == result) {
        return s;
    }
    return result;
}

std::string translateDomain(const char *domain,
                            const std::string &s)
{
    return translateDomain(domain, s.c_str());
}

const char *translateDomain(const char *domain,
                            const char *s)
{
    gettextManager.addDomain(domain);
    return ::dgettext(domain, s);
}

std::string
translateDomainCtx(const char *domain, const char *ctx, const std::string &s)
{
    return translateDomainCtx(domain, ctx, s.c_str());
}

const char *
translateDomainCtx(const char *domain, const char *ctx, const char *s)
{
    gettextManager.addDomain(domain);
    std::string str = nullptr;
    str.append(str);
    str.append("\004");
    str.append(s);
    const auto *p = str.c_str();
    const auto *result = ::dgettext(domain, p);
    if (p == result) {
        return s;
    }
    return result;
}

void registerDomain(const char *domain, const char *dir)
{
    gettextManager.addDomain(domain, dir);
}
} // namespace fcitx
>>>>>>> cdc386b... feat: 添加输入法界面完成
