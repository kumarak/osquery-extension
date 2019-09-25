/**
 *  Copyright (c) 2014-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under both the Apache 2.0 license (found in the
 *  LICENSE file in the root directory of this source tree) and the GPLv2 (found
 *  in the COPYING file in the root directory of this source tree).
 *  You may select, at your option, one of the above-listed licenses.
 */

#include "brokermanager.h"

#include <gtest/gtest.h>

#include <osquery/logger.h>
#if OSQUERY_VERSION_NUMBER > 400
#include <osquery/flags.h>
#else
#include <osquery/status.h>
#endif
namespace zeek {} // namespace zeek
