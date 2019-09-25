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

#include <algorithm>
#include <iostream>
#include <list>
#include <memory>

#include <broker/bro.hh>
#include <broker/broker.hh>
#include <broker/endpoint.hh>

#include <osquery/core.h>
#if OSQUERY_VERSION_NUMBER > 400
#include <osquery/flags.h>
#else
#include <osquery/status.h>
#endif
#include <osquery/system.h>

#include <zeek-remote/ibrokermanager.h>

namespace zeek {
/**
 * @brief Manager class for connections of the broker communication library.
 *
 * The BrokerManager is a singleton to keep track of broker communications and
 * to communicate via the broker endpoint. It provides various ways to retrieve
 * and modify connections. Each 'connection' is technically a subscription to a
 * topic in the publish-subscribe communication.
 *
 * One message_queue (i.e. message inbox) is created for each subscribed topic.
 * Among some predefined topics, joining a group results in subscribing the
 * corresponding topic to receive messages addressed for this group.
 */
class BrokerManager final : public IBrokerManager {
  struct PrivateData;
  std::unique_ptr<PrivateData> d;

  /// Initiates the peering to remote endpoint
  osquery::Status initiatePeering();

  /// Initiates the reset of the broker manager
  osquery::Status initiateReset(bool reset_schedule = true);

  /**
   * @brief Retrieve the latest connection status change
   *
   * Checks for any connection changes and updates cached status to the latest
   * change.
   * Returns the latest cached status if no change occurred within timeout
   *
   * @param timeout duration how long to wait for a status change
   * @return
   */
  std::pair<broker::status, bool> getPeeringStatus(long timeout = 0);

  /**
   * @brief Make the osquery host to announce itself to the remote broker
   * endpoint.
   *
   * This broker message includes the hosts nodeID, groups and network
   * interfaces
   *
   * @return
   */
  void announce();

  /**
   * @brief Reset the BrokerManager to its initial state.
   *
   * This makes the BrokerManager to remove all groups and therefore unsubscribe
   * from all respective broker topics.
   *
   * @return
   */
  osquery::Status reset();

  osquery::Status createSubscriber(const std::string& topic);
  osquery::Status deleteSubscriber(const std::string& topic);

 protected:
  BrokerManager(const Configuration& config, IQueryManager::Ref query_manager);

 public:
  virtual ~BrokerManager() override;

  // IBrokerManager interface
  virtual osquery::Status addGroup(const std::string& group) override;
  virtual osquery::Status removeGroup(const std::string& group) override;

  virtual osquery::Status getSubscriber(BrokerSubscriberRef& subscriber_ref,
                                        const std::string& topic) override;

  virtual std::vector<std::string> getTopics() override;
  virtual osquery::Status checkConnection(long timeout = -1) override;
  virtual int getOutgoingConnectionFD() override;

  virtual osquery::Status logQueryLogItemToZeek(
      const osquery::QueryLogItem& qli) override;

  friend class IBrokerManager;
};
} // namespace zeek
