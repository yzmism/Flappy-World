#ifndef Network_H
#define Network_H

#include "PhxSocket.h"
#include "Pipe.h"
#include "ServerUpdate.h"
#include <memory>

// Event Keys
#define COORDINATES_UPDATE_KEY "coordinates_update"

/*!< Callback used for getting Leaderboard results.
  If able to retrieve results, success will be true. */
using GetLeaderBoardCallback
    = std::function<void(bool success, nlohmann::json json)>;

/*|< Callback used for joining a game room.
   If able to join results, success with be true, and json will hold room description */
using JoinRoomCallback
    = std::function<void(bool success, nlohmann::json json)>;

/*!< Typedef for callback used in Network pubsub. */
using PubSubCallback = std::function<void(bool success, nlohmann::json json)>;

class PhxChannel;

class Network : public std::enable_shared_from_this<PhxSocketDelegate>,
                public PhxSocketDelegate {

private:
    // PhxSocketDelegate
    void phxSocketDidOpen();
    void phxSocketDidClose(const std::string& event);
    void phxSocketDidReceiveError(const std::string& error);
    // PhxSocketDelegate

    /*!< This is the channel for the current room the player has joined. */
    std::shared_ptr<PhxChannel> roomChannel;

    /*!< The socket used by the various Phoenix Channels game uses. */
    std::shared_ptr<PhxSocket> socket;

    /*!< Map that maps events (keys) to array of callbacks. */
    std::unordered_map<std::string,
        std::vector<std::tuple<void*, PubSubCallback>>>
        subscriberMap;

public:
    /**
     *  \brief Network Singleton.
     *
     *  Return a Network singleton.
     *
     *  \return Network
     */
    static std::shared_ptr<Network> getInstance();

    /**
      *  \brief Trigger start of Network connection.
      *
      *  Detailed description
      *
      *  \param param
      *  \return return type
      */
    void start();

    /**
     * /brief Join Stage operation
     *
     * /param callback The callback call when stage joined
     * /return void
     */
    void joinRoom(JoinRoomCallback callback);

    /**
     *  \brief Get Leaderboard results.
     *
     *  Get Leaderboard results from server and return results in callback.
     *
     *  \param callback The callback called when results are retrieved.
     *  \return void
     */
    void getLeaderboard(GetLeaderBoardCallback callback);

    /**
     *  \brief Push an update to channel.
     *
     *  Pushes an update to a Phoenix Channel.
     *
     *  \param update to push to server.
     *  \return void
     */
    void updateServer(std::shared_ptr<ServerUpdate> update);

    /**
     *  \brief Pubsub entry point.
     *
     *  Allow callers to subscribe to event designated by key. When event is
     *  triggered, callback is called.
     *
     *  \param key to subscribe to.
     *  \param ref used to subscribe.
     *  \param callback to run when event is triggered.
     *  \return void
     */
    void subscribe(const std::string& key, void* ref, PubSubCallback callback);

    /**
     *  \brief Unsubscribe listener.
     *
     *  Detailed description
     *
     *  \param to unsubscribe from.
     *  \param ref to unsubscribe.
     *  \return void
     */
    void unsubscribe(const std::string& key, void* ref);
};

#endif // Network_H
