/**
* Copyright (c) 2018 Zilliqa 
* This source code is being disclosed to you solely for the purpose of your participation in 
* testing Zilliqa. You may view, compile and run the code for that purpose and pursuant to 
* the protocols and algorithms that are programmed into, and intended by, the code. You may 
* not do anything else with the code without express permission from Zilliqa Research Pte. Ltd., 
* including modifying or publishing the code (or any part of it), and developing or forming 
* another public or private blockchain network. This source code is provided ‘as is’ and no 
* warranties are given as to title or non-infringement, merchantability or fitness for purpose 
* and, to the extent permitted by law, all liability for your use of the code is disclaimed. 
* Some programs in this code are governed by the GNU General Public License v3.0 (available at 
* https://www.gnu.org/licenses/gpl-3.0.en.html) (‘GPLv3’). The programs that are governed by 
* GPLv3.0 are those programs that are located in the folders src/depends and tests/depends 
* and which include a reference to GPLv3 in their program files.
**/

#include "PeerStore.h"

using namespace std;

PeerStore::PeerStore() = default;

PeerStore::~PeerStore() = default;

PeerStore& PeerStore::GetStore()
{
    static PeerStore ps;
    return ps;
}

void PeerStore::AddPeer(const PubKey& key, const Peer& peer)
{
    lock_guard<mutex> g(m_mutexStore);
    m_store[key] = peer;
}

unsigned int PeerStore::GetPeerCount() const { return m_store.size(); }

Peer PeerStore::GetPeer(const PubKey& key)
{
    lock_guard<mutex> g(m_mutexStore);
    try
    {
        return m_store.at(key);
    }
    catch (out_of_range& e)
    {
        return Peer(0, 0);
    }
}

vector<Peer> PeerStore::GetAllPeers() const
{
    vector<Peer> result;

    for (const auto& it : m_store)
    {
        result.push_back(it.second);
    }

    return result;
}

vector<PubKey> PeerStore::GetAllKeys() const
{
    vector<PubKey> result;

    for (const auto& it : m_store)
    {
        result.push_back(it.first);
    }

    return result;
}

void PeerStore::RemovePeer(const PubKey& key)
{
    lock_guard<mutex> g(m_mutexStore);
    m_store.erase(key);
}

void PeerStore::RemoveAllPeers()
{
    lock_guard<mutex> g(m_mutexStore);
    m_store.clear();
}