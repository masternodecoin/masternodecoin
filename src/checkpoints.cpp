// Copyright (c) 2009-2017 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "proofs.h"
#include "txdb.h"
#include "main.h"
#include "uint256.h"

static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
	typedef std::map<int, uint256> MapCheckpoints;
    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
          (0,     Params().HashGenesisBlock())
        (1, uint256("0x0000000008f710a0e18d0d04a4b86341346611b3e7984f5ee5b3d9010caa0d38"))
        (1000, uint256("0x0000000095750ba4eb4f8d7ac82af03400209e111df3667e51fb6d9cda6edf4d"))
        (2000, uint256("0x000000005fdbc5bf8389f15596a06872663e68d49dd84e87de9d2a0494041fec"))
        (3000, uint256("0x267761f6aa6eb9b96a4c48e593cf17ed7572dc91125e0e5eeb8ba3ec2efda1d1"))
        (5000,     uint256("0x411c6b3f7d7730d851536b7a7ce95d0ba3b4f7c8c4c24142e9b01c469d6e9439") )
        (10000,    uint256("0xe044586abcaae3cb6e7b4756713136ca538c30d0e885edc6a3af6e681b480d05") )
        (20000,    uint256("0x255d7cf5cbb7eece52fc6752be56c4f180b1bf71d83bbee04b84f33cf498c499") )
        (30000,    uint256("0xe6bfd03712c8146cc558ecffad3bd529fec3f15eea08b3e8d38f5a4e7c57a2de") )
        (40000,    uint256("0x11d58efe6ecb82d3c0d3d1dbc3b9cc51460890afe047ac2211da71cc32f8f127") )
        (50000,    uint256("0xe482040a0ab71589b23dd2fe257d67a2f2712dafb085079d76c6c46dbef91c87") )
        (60000,    uint256("0xd38b50003666d67bc340bb2343fdc1ebbde36ce597f7975ac3b813b1eb46d184") )
        (70000,    uint256("0xd8cb10c2f2dd34c75d7e6ea80ae656543bf1f37ae497d4c521e55180abc51bbb") )
    /*    (20000,    uint256("0x255d7cf5cbb7eece52fc6752be56c4f180b1bf71d83bbee04b84f33cf498c499") )
                (30000,    uint256("0xe6bfd03712c8146cc558ecffad3bd529fec3f15eea08b3e8d38f5a4e7c57a2de") )
                (40000,    uint256("0x11d58efe6ecb82d3c0d3d1dbc3b9cc51460890afe047ac2211da71cc32f8f127") )
                (50000,    uint256("0xe482040a0ab71589b23dd2fe257d67a2f2712dafb085079d76c6c46dbef91c87") )
        */
		;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
