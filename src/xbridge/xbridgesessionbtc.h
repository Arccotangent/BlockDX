//*****************************************************************************
//*****************************************************************************

#ifndef XBRIDGESESSIONBTC_H
#define XBRIDGESESSIONBTC_H

#include "xbridge.h"
#include "xbridgesession.h"
#include "xbridgepacket.h"
#include "xbridgetransaction.h"
#include "xbridgewallet.h"
#include "FastDelegate.h"
#include "uint256.h"

#include <memory>
#include <set>
#include <boost/thread/mutex.hpp>
#include <boost/noncopyable.hpp>

//*****************************************************************************
//*****************************************************************************
class XBridgeSessionBtc
        : public XBridgeSession
{
public:
    XBridgeSessionBtc();
    XBridgeSessionBtc(const WalletParam & wallet);
    virtual ~XBridgeSessionBtc();

public:
    std::shared_ptr<XBridgeSessionBtc> shared_from_this()
    {
        return std::static_pointer_cast<XBridgeSessionBtc>(XBridgeSession::shared_from_this());
    }

protected:
    std::string fromXAddr(const std::string & addr) const;
    std::vector<unsigned char> toXAddr(const std::string & addr) const;

    virtual uint32_t lockTime(const char role) const;
    virtual xbridge::CTransactionPtr createTransaction() const;
    virtual xbridge::CTransactionPtr createTransaction(const std::vector<std::pair<std::string, int> > & inputs,
                                                       const std::vector<std::pair<CScript, double> > & outputs,
                                                       const uint32_t lockTime = 0) const;

    virtual bool signTransaction(const xbridge::CKey & key,
                                 const xbridge::CTransactionPtr & transaction,
                                 const uint32_t inputIdx,
                                 const CScript & unlockScript,
                                 std::vector<unsigned char> & signature);
};

typedef std::shared_ptr<XBridgeSessionBtc> XBridgeSessionBtcPtr;

#endif // XBRIDGESESSIONBTC_H
