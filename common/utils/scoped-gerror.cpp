/*
 *  Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Contact: Jan Olszak <j.olszak@samsung.com>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License
 */

/**
 * @file
 * @author  Jan Olszak (j.olszak@samsung.com)
 * @brief   Implementation of the wrapper for GError
 */

#include "config.hpp"

#include "utils/scoped-gerror.hpp"

namespace utils {

ScopedGError::ScopedGError()
    : mError(NULL)
{
}

ScopedGError::ScopedGError(ScopedGError&& other)
    : mError(other.mError)
{
    other.mError = NULL;
}

ScopedGError::~ScopedGError()
{
    if (mError) {
        g_error_free(mError);
    }
}

bool ScopedGError::strip()
{
    return g_dbus_error_strip_remote_error(mError);
}

ScopedGError::operator bool () const
{
    return mError != nullptr;
}

GError** ScopedGError::operator& ()
{
    return &mError;
}

const GError* ScopedGError::operator->() const
{
    return mError;
}

std::ostream& operator<<(std::ostream& os, const ScopedGError& e)
{
    os << e->message;
    return os;
}

} // namespace utils
