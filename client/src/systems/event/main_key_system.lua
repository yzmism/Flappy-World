local main_key_system = class("main_key_system", System)
local log = require('logger.log')

function main_key_system:fireEvent(event)
  log.trace('fireEvent', event, event.key)

  if event.key == "space" then
    for _, entity in pairs(_G.engine:getEntitiesWithComponent("player_bird")) do
      log.trace('updating linear velocity')
      entity:get("physic").body:setLinearVelocity(0, -400)
    end
  end
end

return main_key_system
