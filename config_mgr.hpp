
#define CONFIG_MGR_HPP
/*

        Author : Dimitris Vlachos / DimitrisV22@gmail.com
        Git : https://github.com/DimitrisVlachos
*/

#ifndef _config_mgr_hpp_
#define _config_mgr_hpp_

#include <iostream>
#include <fstream>
#include <stdint.h>
#include <unordered_map>
#include "string_utils.hpp"

class config_manager_c {
    private:
    const std::string k_generic_error_string = "0";
    std::unordered_map<std::string,std::string> m_cfg;
    std::string m_loaded_file;

    inline const std::string* get_entry(const std::string& id) const {
        auto p = m_cfg.find(id);
        if (p == m_cfg.end())
            return &k_generic_error_string;

        return &p->second;
    }

    inline bool get_entry_ex(const std::string& id,std::string& res) const {
        auto p = m_cfg.find(id);
        if (p == m_cfg.end())
            return false;

        res = p->second;
        return true;
    }

    inline void update_entry(const std::string& id,const std::string& v) {
        auto p = m_cfg.find(id);
        if (p == m_cfg.end()) {
            m_cfg.insert({id,v});
            return;
        }

        p->second = v;
    }

    //TODO
    bool load_chunk(const std::string& fn,std::vector<char>& res) {
        return false;
    }
    public:

    config_manager_c(const std::string& path) {  load(path); }
    config_manager_c() : m_loaded_file("null") {}
    ~config_manager_c() {}

    //Get
    inline const std::string& gets(const std::string& id) const {
        auto e = get_entry(id);
        if (!e) {
            static const std::string def_ret="null";
            return def_ret;
        }
        return *e;
    }

    inline const bool gets_ex(const std::string& id,std::string& res) const {
        return get_entry_ex(id,res);
    }

    inline void gets(const std::string& id,std::vector<std::string>& res,const std::string& delim_list=",",const bool skip_whitespace = true) {
        res.clear();
        std::string s;
        if (!gets_ex(id,s))
            return;
        string_utils::split_string(s,delim_list,res,skip_whitespace);
    }

    inline void geti(const std::string& id,std::vector<int32_t>& res,const std::string& delim_list=",",const bool skip_whitespace = true) {
        res.clear();
        std::string s;
        if (!gets_ex(id,s))
            return;
        string_utils::split_string(s,delim_list,res,skip_whitespace);
    }

    inline void getd(const std::string& id,std::vector<double>& res,const std::string& delim_list=",",const bool skip_whitespace = true) {
        res.clear();
        std::string s;
        if (!gets_ex(id,s))
            return;
        string_utils::split_string(s,delim_list,res,skip_whitespace);
    }

    inline int32_t geti(const std::string& id) const {
        return std::stoi(gets(id));
    }

    inline double getd(const std::string& id) const {
        return std::stod(gets(id));
    }

    inline float getf(const std::string& id) const {
        return std::stof(gets(id));
    }

    inline bool getb(const std::string& id) const {
        return (std::stoi(gets(id)) == 0) ? false : true;
    }

    //Set
    inline void sets(const std::string& id,const std::string& v) {
        update_entry(id,v);
    }

    inline void seti(const std::string& id,const int32_t v) {
        update_entry(id,std::to_string(v));
    }

    inline void setd(const std::string& id,const double v) {
        update_entry(id,std::to_string(v));
    }

    inline void setf(const std::string& id,const float v) {
        update_entry(id,std::to_string(v));
    }

    inline void setb(const std::string& id,const bool v) {
        update_entry(id,std::to_string((v) ? 1 : 0));
    }

    //Load
    bool load(const std::string& path) {
        std::ifstream fp;
        fp.open(path.c_str());
        if (!fp.is_open()) {
            std::cout << "Unable to find : " << path << std::endl;
            return false;
        }

        std::string buf;
        std::string id;
        std::string data;

        while (std::getline(fp,buf)) {
            size_t eq_pos = buf.find('=');
            if (eq_pos == std::string::npos)
                continue;
            id="";
            for (size_t i = 0;i < eq_pos;++i) {
                if (isspace(buf[i]))
                    continue;
                id += buf[i];
            }
            size_t start = buf.find('\"',eq_pos+1);
            if (start == std::string::npos)
                continue;
            size_t end = buf.find('\"',start+1);
            if (end == std::string::npos)
                continue;
            data="";
            for (size_t i = start+1;i < end;++i)
                data += buf[i];
            update_entry(id,data);
        }


        m_loaded_file = path;
        return true;
    }

    //Store
    bool store(const std::string& path) {
        std::ofstream fp;
        fp.open(path.c_str());
        if (!fp.is_open())
            return false;

        for (auto p = m_cfg.begin();p != m_cfg.end();++p) {
            fp << p->first << "=\""  << p->second << "\"\r\n";
        }
        fp.close();
        return true;
    }

    bool update() {
        return store(m_loaded_file);
    }
};
#endif
