#include "engine/core/string/StringTable.hpp"
#include "engine/core/helpers/Hash.hpp"

std::unordered_map<std::string, std::unique_ptr<StringIntern>> StringTable::strings;

const StringIntern* StringTable::Intern(std::string_view str) 
{
    auto [iter, inserted] = strings.emplace(str, std::make_unique<StringIntern>());

    if (inserted)
    {
        iter->second->text = iter->first;
        iter->second->hash = fnv1a_64(iter->first);
    }

    return iter->second.get();
}
