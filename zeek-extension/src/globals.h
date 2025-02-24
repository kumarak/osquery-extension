/**
 *  Copyright (c) 2014-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under both the Apache 2.0 license (found in the
 *  LICENSE file in the root directory of this source tree) and the GPLv2 (found
 *  in the COPYING file in the root directory of this source tree).
 *  You may select, at your option, one of the above-listed licenses.
 */

#pragma once

#include "zeekconfiguration.h"

#include <zeek-remote/ibrokermanager.h>
#include <zeek-remote/iquerymanager.h>

namespace zeek {
extern ZeekConfiguration::Ref configuration;
extern IQueryManager::Ref query_manager;
extern IBrokerManager::Ref broker_manager;

osquery::Status initializeGlobals();
} // namespace zeek
