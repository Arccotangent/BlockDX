//*****************************************************************************
//*****************************************************************************

#ifndef XBRIDGEWALLETCONNECTORBTC_H
#define XBRIDGEWALLETCONNECTORBTC_H

#include "xbridgewalletconnector.h"

//*****************************************************************************
//*****************************************************************************
class XBridgeBtcWalletConnector : public XBridgeWalletConnector
{
public:
    XBridgeBtcWalletConnector();

public:
    // reimplement for currency
    std::string fromXAddr(const std::vector<unsigned char> & xaddr) const;
    std::vector<unsigned char> toXAddr(const std::string & addr) const;

public:
    bool requestAddressBook(std::vector<wallet::AddressBookEntry> & entries);

    bool getUnspent(std::vector<wallet::UtxoEntry> & inputs) const;
    bool lockUnspent(const std::vector<wallet::UtxoEntry> & inputs, const bool lock = true) const;

    bool getRawTransaction(const std::string & txid, const bool verbose, std::string & tx);

    bool getNewAddress(std::string & addr);

    bool createRawTransaction(const std::vector<std::pair<std::string, int> > & inputs,
                              const std::vector<std::pair<std::string, double> > & outputs,
                              const uint32_t lockTime,
                              std::string & tx);

    bool signRawTransaction(std::string & rawtx, bool & complete);

    bool signRawTransaction(std::string & rawtx,
                            const std::vector<std::tuple<std::string, int, std::string, std::string> > & prevtxs,
                            const std::vector<std::string> & keys,
                            bool & complete);

    bool decodeRawTransaction(const std::string & rawtx,
                              std::string & txid,
                              std::string & tx);

    bool decodeRawTransaction(const std::string & rawtx,
                              std::vector<std::pair<std::string, int> > & prevtx,
                              std::string & scriptPubKey);

    bool sendRawTransaction(const std::string & rawtx,
                            std::string & txid,
                            int32_t & errorCode);

public:
    bool newKeyPair(std::vector<unsigned char> & pubkey, std::vector<unsigned char> & privkey);

    std::vector<unsigned char> getKeyId(const std::vector<unsigned char> & pubkey);
    std::vector<unsigned char> getScriptId(const std::vector<unsigned char> & script);
    std::string scriptIdToString(const std::vector<unsigned char> & id) const;

    double minTxFee1(const uint32_t inputCount, const uint32_t outputCount);
    double minTxFee2(const uint32_t inputCount, const uint32_t outputCount);

    bool checkTransaction(const std::string & depositTxId,
                          const std::string & /*destination*/,
                          const uint64_t & /*amount*/,
                          bool & isGood);

    uint32_t lockTime(const char role) const;

    bool createDepositUnlockScript(const std::vector<unsigned char> & myPubKey,
                                   const std::vector<unsigned char> & otherPubKey,
                                   const std::vector<unsigned char> & xdata,
                                   const uint32_t lockTime,
                                   std::vector<unsigned char> & resultSript);

    bool createDepositTransaction(const std::vector<std::pair<std::string, int> > & inputs,
                                  const std::vector<std::pair<std::string, double> > & outputs,
                                  std::string & txId,
                                  std::string & rawTx);

    bool createRefundTransaction(const std::vector<std::pair<std::string, int> > & inputs,
                                 const std::vector<std::pair<std::string, double> > & outputs,
                                 const std::vector<unsigned char> & mpubKey,
                                 const std::vector<unsigned char> & mprivKey,
                                 const std::vector<unsigned char> & innerScript,
                                 const uint32_t lockTime,
                                 std::string & txId,
                                 std::string & rawTx);

    bool createPaymentTransaction(const std::vector<std::pair<std::string, int> > & inputs,
                                  const std::vector<std::pair<std::string, double> > & outputs,
                                  const std::vector<unsigned char> & mpubKey,
                                  const std::vector<unsigned char> & mprivKey,
                                  const std::vector<unsigned char> & xpubKey,
                                  const std::vector<unsigned char> & innerScript,
                                  std::string & txId,
                                  std::string & rawTx);
};

#endif // XBRIDGEWALLETCONNECTORBTC_H
