#pragma once

#include <RakPeerInterface.h>
#include <BitStream.h>
#include <PacketLogger.h>
#include <MessageIdentifiers.h>
#include <iostream>

#include "../../core/memory/memory_object.h"
#include "../../core/console/message.h"

using namespace blowbox::memory;

namespace RakNet
{
	class RakPeerInterface;
	struct SystemAddress;
}

namespace blowbox
{
	/**
	* @class blowbox::Console
	* @author Riko Ophorst
	* @brief Enables communication with external console through RakNet
	*/
	class Console : public memory::MObject
	{
	public:
		/**
		* @brief Console constructor
		* @param[in]	allocator	The allocator used to allocate this Console instance
		*/
		Console(memory::Allocator* allocator);

		~Console(); //<! Console destructor

		/**
		* @brief Factory to create the Console
		* @param[in]	allocator	The allocator that should be used to allocate the Console instance
		*/
		static Console* Create(memory::Allocator* allocator);
		
		static Console* Instance(); //<! Get the Console instance
		void Connect(); //<! Connect to the external console server
		void Disconnect(); //<! Disconnect from the external console server

		/**
		* @brief Logs a message to the external console
		* @param[in]	message		The message to be sent
		*/
		void Log(Message* message);

		/**
		* @brief Logs a message to the external console
		* @param[in]	log		The actual log to be logged
		* @param[in]	type	The type of log
		*/
		void Log(const std::string& log, BB_MESSAGE_TYPES type);
	private:
		static Console* instance_; //<! Singleton instance of Console

		LinearAllocator* temp_message_allocator_; //<! Temporary message allocator

		RakNet::RakPeerInterface* peer_; //<! Stores the peer information
		RakNet::SystemAddress server_; //<! The server address of the external console
		bool peer_started_; //<! Has the peer started?
		bool connection_attempt_started_; //<! Has the connection attempted to start?
		bool connected_; //<! Are we connected?
	};
}