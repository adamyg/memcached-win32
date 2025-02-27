#pragma once
#ifndef SIMPLECONFIG_H_INCLUDED
#define SIMPLECONFIG_H_INCLUDED
/* -*- mode: c; indent-width: 8; -*- */
/*
 * Simple config
 *
 * Copyright (c) 2020 - 2025, Adam Young.
 * All rights reserved.
 *
 * The applications are free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * Redistributions of source code must retain the above copyright
 * notice, and must be distributed with the license document above.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, and must include the license document above in
 * the documentation and/or other materials provided with the
 * distribution.
 *
 * This project is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * license for more details.
 * ==end==
 */

#include <string>
#include <string.h>
#include <map>
#include <vector>

#include <cctype>
#include <utility>

#include "w32support.h"

class Config {
        BOOST_DELETED_FUNCTION(Config(const Config &))
        BOOST_DELETED_FUNCTION(Config& operator=(const Config &))

public:
        struct string_view {
                string_view(const char *_data, unsigned _length) :
                        data(_data), length(_length) {
                }
                string_view(const char *_data) :
                        data(_data), length(_data ? strlen(_data) : 0) {
                }
                const char *data;
                unsigned length;
        };

        struct iless {
                typedef unsigned is_transparent;
                        // transparent comparator, allow alternative comparsion types.

                static inline unsigned char Normalise(unsigned char ch) {
                        if (ch >= 'A' && ch <= 'Z') // tolower
                                return ch - ('A' - 'a');
                        if (ch == '/')
                                return '\\';    // equiv
                        return ch;
                }

                static inline int Strcasecmp(const char *lhs, const char *rhs) {
                        const unsigned char *ls = (const unsigned char *)lhs,
                                *rs = (const unsigned char *)rhs;
                        int l, r;
                        do {
                                l = Normalise(*ls++), r = Normalise(*rs++);
                        } while (l && (l == r));
                        return (l - r);
                }

                static inline int Strcasecmp(const char *lhs, unsigned lhn, const char *rhs, unsigned rhn) {
                        const unsigned char *ls = (const unsigned char *)lhs,
                                *rs = (const unsigned char *)rhs;
                        for (;;) {
                                const unsigned char lc = (lhn-- ? *ls++ : 0);
                                const unsigned char rc = (rhn-- ? *rs++ : 0);
                                if (lc != rc) {
                                        const int l = Normalise(lc), r = Normalise(rc);
                                        if (l != r) {
                                                return (l - r);
                                        }
                                }
                                if (lc == 0)    // eos
                                        return 0;
                        }
                        /*NOTREACHED*/
                }

                bool operator()(const std::string &lhs, const std::string &rhs) const {
                        return Strcasecmp(lhs.c_str(), rhs.c_str()) < 0;
                }

                bool operator()(const char *lhs, const std::string &rhs) const {
                        return Strcasecmp(lhs, rhs.c_str()) < 0;
                }

                bool operator()(const std::string &lhs, const char *rhs) const {
                        return Strcasecmp(lhs.c_str(), rhs) < 0;
                }

                bool operator()(const Config::string_view &lhs, const std::string &rhs) const {
                        const unsigned char *ls = (const unsigned char *)lhs.data,
                                *rs = (const unsigned char *)rhs.c_str();
                        unsigned ln = lhs.length;
                        for (;;) {
                                const unsigned char lc = (ln-- ? *ls++ : 0);
                                const unsigned char rc = *rs++;
                                if (lc != rc) {
                                        const int l = Normalise(lc), r = Normalise(rc);
                                        if (l != r) {
                                                return (l - r) < 0;
                                        }
                                }
                                if (lc == 0)    // eos
                                        return 0;
                        }
                }

                bool operator()(const std::string &lhs, const Config::string_view &rhs) const {
                        const unsigned char *ls = (const unsigned char *)lhs.c_str(),
                                *rs = (const unsigned char *)rhs.data;
                        unsigned rn = rhs.length;
                        for (;;) {
                                const unsigned char lc = *ls++;
                                const unsigned char rc = (rn-- ? *rs++ : 0);
                                if (lc != rc) {
                                        const int l = Normalise(lc), r = Normalise(rc);
                                        if (l != r) {
                                                return (l - r) < 0;
                                        }
                                }
                                if (lc == 0)    // eos
                                        return 0;
                        }
                }
        };

#if defined(__WATCOMC__) || defined(__MINGW32__)
        typedef std::map<std::string, std::string, iless> collection_impl;
        struct collection_t : public collection_impl {
                const_iterator find(const std::string &value) const {
                        return ((collection_impl *)this)->find(value);
                }
                const_iterator find(const Config::string_view &value) const {
                        const std::string t_value(value.data, value.length);
                        return ((collection_impl *)this)->find(t_value);
                }
                const_iterator find(const char *value) const {
                        return ((collection_impl *)this)->find(value);
                }
        };
#else
        typedef std::map<std::string, std::string, iless> collection_t;
#endif
        typedef std::vector<std::pair <std::string, std::string>/**/> elements_t;

private:
        struct values_t {
                collection_t collection;
                elements_t elements;

                void insert(const std::string &key, const std::string &value)
                {
                        collection.insert(std::make_pair(key, value));
                        elements.push_back(std::make_pair(key, value));
                }
        };

#if defined(__WATCOMC__) || defined(__MINGW32__)
        typedef std::map<std::string, values_t *, iless> sections_impl;
        struct sections_t : public sections_impl {
                const_iterator find(const std::string &value) const {
                        return ((sections_impl *)this)->find(value);
                }
                const_iterator find(const Config::string_view &value) const {
                        const std::string t_value(value.data, value.length);
                        return ((sections_impl *)this)->find(t_value);
                }
                const_iterator find(const char *value) const {
                        return ((sections_impl *)this)->find(value);
                }
        };
#else
        typedef std::map<std::string, values_t *, iless> sections_t;
#endif

public:
        Config();
        virtual ~Config();

public:
        bool Load(const std::string &file, std::string &errmsg);
        bool empty() const;
        void clear();

        bool HasSection(const std::string &section) const;
        bool HasSection(const Config::string_view &section) const;
        bool HasSection(const char *section) const;

        bool GetSections(std::vector<std::string> &sections) const;
        const elements_t *GetSectionElements(const std::string &section) const;

        bool GetKeys(const std::string &section, std::vector <std::string> &keys) const;
        bool GetKeys(const Config::string_view &section, std::vector <std::string> &keys) const;
        bool GetKeys(const char *section, std::vector <std::string> &keys) const;

        const std::string &GetValue(const std::string &section, const std::string &key) const;
        const std::string &GetValue(const Config::string_view &section, const Config::string_view &key) const;
        const std::string &GetValue(const std::string &section, const std::string &key, const std::string &def) const;

        const std::string *GetValuePtr(const std::string &section, const std::string &key, const std::string *def = 0) const;
        const std::string *GetValuePtr(const Config::string_view &section, const Config::string_view &key, const std::string *def = 0) const;
        const std::string *GetValuePtr(const char *section, const char *key, const std::string *def = 0) const;

private:
        values_t *FetchSection(const std::string &section);

private:
        sections_t sections_;
};

#endif  //SIMPLECONFIG_H_INCLUDED

