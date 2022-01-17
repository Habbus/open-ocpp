/*
Copyright (c) 2020 Cedric Jimenez
This file is part of OpenOCPP.

OpenOCPP is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenOCPP is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with OpenOCPP. If not, see <http://www.gnu.org/licenses/>.
*/

#include "ChangeConfiguration.h"
#include "IRpcClient.h"

using namespace ocpp::types;

namespace ocpp
{
namespace types
{
/** @brief Helper to convert a ConfigurationStatus enum to string */
const EnumToStringFromString<ConfigurationStatus> ConfigurationStatusHelper = {{ConfigurationStatus::Accepted, "Accepted"},
                                                                               {ConfigurationStatus::Rejected, "Rejected"},
                                                                               {ConfigurationStatus::RebootRequired, "RebootRequired"},
                                                                               {ConfigurationStatus::NotSupported, "NotSupported"}};
} // namespace types

namespace messages
{

/** @copydoc bool IMessageConverter<DataType>::fromJson(const rapidjson::Value&, DataType&, const char*&, std::string&) */
bool ChangeConfigurationReqConverter::fromJson(const rapidjson::Value& json,
                                               ChangeConfigurationReq& data,
                                               const char*&            error_code,
                                               std::string&            error_message)
{
    (void)error_code;
    (void)error_message;
    extract(json, "key", data.key);
    extract(json, "value", data.value);
    return true;
}

/** @copydoc bool IMessageConverter<DataType>::toJson(DataType&, rapidjson::Document&, const char*&, std::string&) */
bool ChangeConfigurationReqConverter::toJson(const ChangeConfigurationReq& data, rapidjson::Document& json)
{
    fill(json, "key", data.key);
    fill(json, "value", data.value);
    return true;
}

/** @copydoc bool IMessageConverter<DataType>::fromJson(const rapidjson::Value&, DataType&, const char*&, std::string&) */
bool ChangeConfigurationConfConverter::fromJson(const rapidjson::Value&  json,
                                                ChangeConfigurationConf& data,
                                                const char*&             error_code,
                                                std::string&             error_message)
{
    (void)error_code;
    (void)error_message;
    data.status = ConfigurationStatusHelper.fromString(json["status"].GetString());
    return true;
}

/** @copydoc bool IMessageConverter<DataType>::toJson(DataType&, rapidjson::Document&, const char*&, std::string&) */
bool ChangeConfigurationConfConverter::toJson(const ChangeConfigurationConf& data, rapidjson::Document& json)
{
    fill(json, "status", ConfigurationStatusHelper.toString(data.status));
    return true;
}

} // namespace messages
} // namespace ocpp