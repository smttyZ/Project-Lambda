#pragma once
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace lambda::core {

class ArgParser {
public:
    explicit ArgParser(int argc, char* argv[]) {
        for (int i = 1; i < argc; ++i) {
            std::string key = argv[i];
            if (key.compare(0, 2, "--") == 0) {
                key = key.substr(2);
                if (i + 1 < argc && argv[i + 1][0] != '-') {
                    args_[key] = argv[++i];
                } else {
                    args_[key] = "true"; // flag-style (no value)
                }
            }
        }
    }

    bool Has(std::string_view key) const {
        return args_.contains(std::string(key));
    }

    std::string Get(std::string_view key, std::string_view def = "") const {
        if (auto it = args_.find(std::string(key)); it != args_.end()) return it->second;
        return std::string(def);
    }

    double GetDouble(std::string_view key, double def = 0.0) const {
        if (auto it = args_.find(std::string(key)); it != args_.end())
            return std::stod(it->second);
        return def;
    }

private:
    std::unordered_map<std::string, std::string> args_;
};

} // namespace lambda::core