#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
#pragma once
/*
 * Simple config
 *
 * Copyright (c) 2020, Adam Young.
 * All rights reserved.
 *
 * This file is part of memcached-win32.
 *
 * The applications are free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
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
 * ==end==
 */

#include <string>
#include <map>
#include <vector>

#include "w32support.h"

class Config {
        BOOST_DELETED_FUNCTION(Config(const Config &))
        BOOST_DELETED_FUNCTION(Config& operator=(const Config &))

public:
        struct iless : public std::binary_function<std::string, std::string, bool> {
                bool operator()(const std::string &lhs, const std::string &rhs) const {
                        return _stricmp(lhs.c_str(), rhs.c_str()) < 0;
                }
        };

        typedef std::map<std::string, std::string> collection_t;
        typedef std::vector< std::pair <std::string, std::string>> elements_t;

private:
        typedef struct {
                collection_t collection;
                elements_t elements;

                void insert(const std::string &key, const std::string &value) {
                        collection.insert(std::make_pair(key, value));
                        elements.push_back(std::make_pair(key, value));
                }
        } values_t;

        typedef std::map<std::string, values_t *, iless> sections_t;

public:
        Config();
        ~Config();

public:
        bool Load(const std::string &file, std::string &errmsg);
        bool empty() const;
        void clear();

        bool HasSection(const std::string &section) const;
        bool GetSections(std::vector<std::string> &sections) const;
        const elements_t *GetSectionElements(const std::string &section) const;

        bool GetKeys(const std:: string &section, std::vector <std::string> &keys) const;
        const std::string GetValue(const std::string &section, const std::string &key) const;
        const std::string GetValue(const std::string &section, const std::string &key, const std::string &def) const;
        const std::string *GetValuePtr(const std::string &section, const std::string &key, const std::string *def = 0) const;

private:
        values_t *FetchSection(const std::string &section);

private:
        sections_t sections_;
};

#endif  //CONFIG_H_INCLUDED
