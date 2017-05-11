#include "lua_raknet.h"

#include <stdio.h>
#include <string.h>
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"  // MessageID
#include "LuaFunction.hpp"
#include <string>

//#define MAX_CLIENTS (200)
static bool isServer = false;

enum GameMessages
{
    ID_GAME_MESSAGE_1=ID_USER_PACKET_ENUM+1
};

static int raknet_GetInstance(lua_State* L) {
    RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
    lua_pushlightuserdata(L, peer);
    return 1;
}

static int raknet_Startup(lua_State* L) {
    RakNet::RakPeerInterface *peer = (RakNet::RakPeerInterface *)lua_touserdata(L, 1);

    int argc = lua_gettop(L);
    printf("argc is %d\r\n",argc);
    if (argc == 1) {
        RakNet::SocketDescriptor sd;
        peer->Startup(1,&sd, 1);
    } else {
        isServer = true;
        unsigned short SERVER_PORT = lua_tointeger(L, 2);
        unsigned short MAX_CLIENTS = lua_tointeger(L, 3);
        printf("SERVER_PORT is %d\r\n",SERVER_PORT);
        printf("MAX_CLIENTS is %d\r\n",MAX_CLIENTS);
        RakNet::SocketDescriptor sd(SERVER_PORT,0);
        peer->Startup(MAX_CLIENTS, &sd, 1);
    }

    return 0;
}

static int raknet_Connect(lua_State* L) {
    RakNet::RakPeerInterface *peer = (RakNet::RakPeerInterface *)lua_touserdata(L, 1);
    const char* ip = lua_tostring(L, 2);
    unsigned short SERVER_PORT = lua_tointeger(L,3);
    printf("ip is %s SERVER_PORT is %d \r\n",ip,SERVER_PORT);
    peer->Connect(ip, SERVER_PORT, 0,0);

    return 0;
}

static int raknet_SetMaximumIncomingConnections(lua_State* L) {
  RakNet::RakPeerInterface *peer = (RakNet::RakPeerInterface *)lua_touserdata(L, 1);
  unsigned short max = lua_tointeger(L, 2);
  peer->SetMaximumIncomingConnections(max);

  return 0;
}

static int raknet_Poll(lua_State* L) {
  RakNet::RakPeerInterface *peer = (RakNet::RakPeerInterface *)lua_touserdata(L, 1);
  LuaFunction callback(L, 2);
  RakNet::Packet *packet;
  for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
  {
      const char * adress = packet->systemAddress.ToString();
      int event = packet->data[0];
      unsigned char* data = NULL;
      if (event == ID_GAME_MESSAGE_1) {
          data = packet->data;
          data = data + 1;
      }

      if (data) {
          std::string sdata((const char*)data,packet->length-1);
          callback(event,adress,sdata);
      } else {
          callback(event,adress);
      }
  }

  return 0;
}

static int raknet_Send(lua_State* L) {
    RakNet::RakPeerInterface *peer = (RakNet::RakPeerInterface *)lua_touserdata(L, 1);
    size_t size;
    const char* data = luaL_checklstring(L, 2,&size);
    const char* address = luaL_checkstring(L, 3);

    RakNet::SystemAddress addr(address);
    RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
    bsOut.Write(data,size);
    peer->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,addr,false);

    return 0;
}

static const luaL_Reg functions[] = {
	{ "GetInstance", raknet_GetInstance },
    { "Startup", raknet_Startup },
    { "Connect", raknet_Connect },
    { "SetMaximumIncomingConnections", raknet_SetMaximumIncomingConnections },
    { "Poll", raknet_Poll },
    { "Send", raknet_Send },
	{ NULL,      NULL}
};

extern "C"  int luaopen_raknet(lua_State *L)
{
  lua_newtable(L);
	luaL_register(L, NULL, functions);
	return 1;
}
