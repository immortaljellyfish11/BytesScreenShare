#pragma once
#include <QObject>
#include <memory>
#include <rtc/rtc.hpp>

#include "signaling-server/src/Common.hpp"

class WsSignalingClient;

class PeerConnectionManager : public QObject {
    Q_OBJECT
public:
    PeerConnectionManager(QObject* parent = nullptr);
    ~PeerConnectionManager();

    void registerClient();
    void start(const QString& targetId);
    void sendEncodedVideoFrame(const QByteArray& encodedData, uint32_t timestamp);
    QString id() const;
    QString target() const;

signals:
    void signalingConnected();
    void signalingError(const QString& msg);
    void peerJoined(const QString& peerId);
    void peersList(const QJsonArray& list);
    void p2pConnected();     // datachannel has established
    void p2pDisconnected();
    void encodedFrameReceived(QByteArray data);

    void connected();
    void disconnected();
    void errorOccurred(const QString& msg);
    void messageReceived(const QString& msg); 
    void dataChannelOpened();

public:
    void onConnectServer(const QString& url);
    void onSignalingMessage(const QJsonObject& obj);
    void onJoined(const QString& peerId);
    void sendEncodedFrame(const QByteArray& data, uint32_t timestamp);
    void stop();

private:
    void handleSignalingMessage(const QJsonObject& json);
    void sendSignalingMessage(const QString& type, const QString& to, const QJsonObject& data);
    void sendtest();
    void createPeerConnection();
    void setupDataChannel();
    void bindDataChannel(std::shared_ptr<rtc::DataChannel> dc);
    void sendRtpPacket(const std::vector<uint8_t>& payload, bool marker);
    
    
    
private:
    std::shared_ptr<rtc::WebSocket> m_ws;
    std::shared_ptr<rtc::PeerConnection> m_pc;
    std::shared_ptr<rtc::DataChannel> m_videoChannel;

    QString m_serverUrl;
    QString m_myId;
    QString m_targetPeerId;
    bool m_isCaller; 
    uint16_t sequenceNumber_ = 0;
    uint32_t ssrc_ = 0;
    // 【新增】RTP 封包需要的状态变量
    uint16_t m_sequenceNumber = 0;
    uint32_t m_ssrc = 323010; // 随便给个 ID
    uint32_t currentTimestamp_ = 0;

    const size_t MAX_RTP_PAYLOAD_SIZE = 1100; // 留出空间给 IP/UDP/RTP 头，保守设为 1100
    const int payloadType_ = 96;
};
