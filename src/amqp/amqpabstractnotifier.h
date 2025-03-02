// Copyright (c) 2017 The ZiCE developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZICE_AMQP_AMQPABSTRACTNOTIFIER_H
#define ZICE_AMQP_AMQPABSTRACTNOTIFIER_H

#include "amqpconfig.h"

class CBlockIndex;
class AMQPAbstractNotifier;

typedef AMQPAbstractNotifier* (*AMQPNotifierFactory)();

class AMQPAbstractNotifier
{
public:
    AMQPAbstractNotifier() { }
    virtual ~AMQPAbstractNotifier();

    template <typename T>
    static AMQPAbstractNotifier* Create()
    {
        return new T();
    }

    std::string GetType() const { return type; }
    void SetType(const std::string &t) { type = t; }
    std::string GetAddress() const { return address; }
    void SetAddress(const std::string &a) { address = a; }

    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;

    virtual bool NotifyBlock(const CBlockIndex *pindex);
    virtual bool NotifyTransaction(const CTransaction &transaction);

protected:
    std::string type;
    std::string address;
};

#endif // ZICE_AMQP_AMQPABSTRACTNOTIFIER_H
