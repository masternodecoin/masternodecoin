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
          (80000,    uint256("0xc3af51f48d51b23a738af34f38d56b30066e6c0d1ad95b18f2a1aff5ddafd3fd") )
          (90000,    uint256("0x17b4cefd793a650a7b87b69223fa7bc68382430be96447c07504ee26ec632211") )
          (100000,   uint256("0xfac73bc88550f6e8682ccb54002744eef7b2b6ff6495fe01618a8dcd3aa33375") )
          (110000,   uint256("0x382b974d4f0282036def807d5229d9d97e97b9a3928a591066f77d1e8e58a9e9") )
          (130000,   uint256("0x3ee4dafd7875038b16b57909692f30c4c553287c487cd56f054b566421995469") )
          (150000,   uint256("0x0e815b1d3385f31b42f552413ccd03c2a1aace2f409ce1e6708c7ba375f19c6a") )
          (160000,   uint256("0x9c823e9bef7b1977bdf2aa81f56d84e3611f8898c8fcafca4b6dcba29678e88f") )
          (170000,   uint256("0xfd3428b280b1e8b00f25c0d34370195aa7c396707d1ac42c7b94ba22c26765a6") )
          (180000,   uint256("0x346d797caeda2a90e0cd313c55b8210852ef9830031804f4d375494942c77b81") )
          (190000,   uint256("0x02adc3301ec840e070bbb3e5f9cb814afca92aa32511801bb6317d3d7148376b") )
          (200000,   uint256("0x99057098c705addb384db3fd7cdf5b56e20c3f25b7d6a77673853416653335cd") )
          (210000,   uint256("0xd77a0ee3874716767bf57c4c069042aca1bb747814a4565beacb5fcab08be131") )
          (220000,   uint256("0xeeaf134d5903095a1b57371e61e42803d80650a12d584abc2fcfd7cca16374d4") )
          (230000,   uint256("0x5598e2bd96af7b4196c36cbe772af28a4976d55196271661e1713ee61f88c662") )
          (240000,   uint256("0x6a7f4955ef370eef576916d0d55e5b8706b259c9d0fb653deae550e4b58d3226") )
          (250000,   uint256("0x319315bc50e11cac98b5e1c623c752152dae619875c238543e2b019ca945c392") )
          (260000,   uint256("0xeea4e7b10824ca0f861fdceb31de38d13149ca98ea6d91a7a7aaa67489bb0226") )
          (270000,   uint256("0x3708c6e7c368546c3f1898899cf9ed64141afd4629aa7deabaaade36ca7bb1da") )
          (280000,   uint256("0x47aea455a98143fc757efa52a34573c933d2ac98a28e5b21caa5f0e1e2a31bca") )
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
