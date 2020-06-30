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

#include <iostream>
#include <fstream>
#include <assert.h>

#include "Config.h"

namespace {
        // left trim
        inline std::string &
        ltrim(std::string &s, const char *c = " \t\n\r\f\v") {
                s.erase(0, s.find_first_not_of(c));
                return s;
        }

        // right trim
        inline std::string &
        rtrim(std::string &s, const char *c = " \t\n\r\f\v") {
                s.erase(s.find_last_not_of(c) + 1);
                return s;
        }

        // trim
        inline std::string &
        trim(std::string &s, const char *c = " \t\n\r\f\v") {
                return ltrim(rtrim(s, c), c);
        }
};


Config::Config()
{
}


Config::~Config()
{
        clear();
}


bool
Config::Load(const std::string &file, std::string &errmsg)
{
        std::ifstream input(file);
        if (! input) return false;

        try {
                values_t *values = FetchSection("");

                for (std::string line; std::getline(input, line); ) {

                        // line
                        //      line.erase(std::remove_if(line.begin(), line.end(), isspace),line.end());
                        //      if (line[0] == '#' || line.empty()) {
                        //              continue;
                        //      }
                        const size_t bang = line.find_first_of("#");
                        if (bang != std::string::npos) {
                                line.erase(bang);
                        }
                        rtrim(line);
                        if (line.empty()) {
                                continue;
                        }

                        // section
                        if (line[0] == '[')  {
                                if (line[line.size()-1] != ']') {
                                        throw std::runtime_error("section format error");
                                }
                                std::string section = std::string(line, 1, line.size() - 2);
                                values = FetchSection(trim(section));
                                continue;
                        }

                        // key [= value]
                        const size_t eq = line.find_first_of("=");
                        if (eq == std::string::npos) {
                                ltrim(line);
                                if (! line.empty()) {
                                        values->insert(line, "");
                                }
                        } else {
                                std::string key = std::string(line, 0, eq),
                                        value = std::string(line, eq + 1, line.size()-1);

                                trim(key);
                                if (! key.empty()) {
                                        values->insert(key, ltrim(value));
                                }
                        }
                }
                input.close();
                return true;

        } catch (std::runtime_error &e) {
                errmsg = e.what();
                clear();
                input.close();
                return false;
        }
        return true;
}


//private
Config::values_t *
Config::FetchSection(const std::string &section)
{
        sections_t::const_iterator it(sections_.find(section));
        if (it != sections_.end()) {
                return it->second;
        }

        values_t *values = new values_t;
        sections_.insert(std::make_pair(section, values));
        return values;
}


void
Config::clear()
{
        for (sections_t::iterator it(sections_.begin()), end(sections_.end()); it != end; ++it) {
                delete it->second;
        }
        sections_.clear();
}


bool
Config::empty() const
{
        return sections_.empty();
}


bool
Config::HasSection(const std::string &section) const
{
        return sections_.find(section) != sections_.end() ? true : false;
}


bool
Config::GetSections(std::vector<std::string> &sections) const
{
        for (sections_t::const_iterator it(sections_.begin()), end(sections_.end()); it != end; ++it) {
                sections.push_back(it->first);
        }
        return true;
}


const Config::elements_t *
Config::GetSectionElements(const std::string &section) const
{
        sections_t::const_iterator it(sections_.find(section));
        if (it != sections_.end()) {
                if (const values_t *values = it->second) {
                        return &values->elements;
                }
        }
        return 0;
}


bool
Config::GetKeys(const std::string &section, std::vector<std::string> &keys) const
{
        sections_t::const_iterator it(sections_.find(section));
        if (it != sections_.end()) {
                if (const values_t *values = it->second) {
                        const collection_t &collection = values->collection;
                        for (collection_t::const_iterator vit(collection.begin()), vend(collection.end()); vit != vend; ++vend) {
                                keys.push_back(vit->first);
                        }
                        return true;
                }
        }
        return false;
}


const std::string
Config::GetValue(const std::string &section, const std::string &key) const
{
        sections_t::const_iterator it(sections_.find(section));
        if (it != sections_.end()) {
                if (const values_t *values = it->second) {
                        const collection_t &collection = values->collection;
                        collection_t::const_iterator cit(collection.find(key));
                        if (cit != collection.end()) {
                                return cit->second;
                        }
                }
        }
        return std::string();
}


const std::string
Config::GetValue(const std::string &section, const std::string &key, const std::string &def) const
{
        sections_t::const_iterator it(sections_.find(section));
        if (it != sections_.end()) {
                if (const values_t *values = it->second) {
                        const collection_t &collection = values->collection;
                        collection_t::const_iterator cit(collection.find(key));
                        if (cit != collection.end()) {
                                return cit->second;
                        }
                }
        }
        return def;
}


const std::string *
Config::GetValuePtr(const std::string &section, const std::string &key, const std::string *def) const
{
        sections_t::const_iterator it(sections_.find(section));
        if (it != sections_.end()) {
                if (const values_t *values = it->second) {
                        const collection_t &collection = values->collection;
                        collection_t::const_iterator cit(collection.find(key));
                        if (cit != collection.end()) {
                                return &cit->second;
                        }
                }
        }
        return def;
}

/*end*/
