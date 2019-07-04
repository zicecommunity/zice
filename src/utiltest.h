// Copyright (c) 2016 The ZiCE developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZICE_UTIL_TEST_H
#define ZICE_UTIL_TEST_H

#include "key_io.h"
#include "wallet/wallet.h"
#include "zice/JoinSplit.hpp"
#include "zice/Note.hpp"
#include "zice/NoteEncryption.hpp"
#include "zice/zip32.h"

// Sprout
CWalletTx GetValidSproutReceive(ZCJoinSplit& params,
                                const libzice::SproutSpendingKey& sk,
                                CAmount value,
                                bool randomInputs,
                                int32_t version = 2);
CWalletTx GetInvalidCommitmentSproutReceive(ZCJoinSplit& params,
                                const libzice::SproutSpendingKey& sk,
                                CAmount value,
                                bool randomInputs,
                                int32_t version = 2);
libzice::SproutNote GetSproutNote(ZCJoinSplit& params,
                                   const libzice::SproutSpendingKey& sk,
                                   const CTransaction& tx, size_t js, size_t n);
CWalletTx GetValidSproutSpend(ZCJoinSplit& params,
                              const libzice::SproutSpendingKey& sk,
                              const libzice::SproutNote& note,
                              CAmount value);

// Sapling
static const std::string T_SECRET_REGTEST = "cND2ZvtabDbJ1gucx9GWH6XT9kgTAqfb6cotPt5Q5CyxVDhid2EN";

struct TestSaplingNote {
    libzice::SaplingNote note;
    SaplingMerkleTree tree;
};

const Consensus::Params& RegtestActivateSapling();

void RegtestDeactivateSapling();

libzice::SaplingExtendedSpendingKey GetTestMasterSaplingSpendingKey();

CKey AddTestCKeyToKeyStore(CBasicKeyStore& keyStore);

/**
 * Generate a dummy SaplingNote and a SaplingMerkleTree with that note's commitment.
 */
TestSaplingNote GetTestSaplingNote(const libzice::SaplingPaymentAddress& pa, CAmount value);

CWalletTx GetValidSaplingReceive(const Consensus::Params& consensusParams,
                                 CBasicKeyStore& keyStore,
                                 const libzice::SaplingExtendedSpendingKey &sk,
                                 CAmount value);

#endif // ZICE_UTIL_TEST_H
