#include "pcapworker.h"


PcapWorker::PcapWorker(QObject *parent)
    : QThread(parent)
{
    ndpi_struct = ndpi_init_detection_module(4);
    if (ndpi_struct == nullptr) {
        qDebug() << "ERROR: Could not initialize nDPI library.";
        return;
    }
}
PcapWorker::~PcapWorker() {
    if (ndpi_struct != nullptr)
        ndpi_exit_detection_module(ndpi_struct);
}
void PcapWorker::run() {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    handle = pcap_open_offline(filename.toLocal8Bit().constData(), errbuf);
    if (handle == nullptr) {
        qDebug() << "Couldn't open pcap file" << filename << ": " << errbuf;
        return;
    }

    // Loop over all packets in the pcap file
    struct pcap_pkthdr header;
    const u_char *packet;
    while ((packet = pcap_next(handle, &header)) != nullptr) {
        // Analyze the packet with nDPI
        // You need to properly set up the flow and id structures, which can be complex
        // For simplicity, we assume here that they are null
        ndpi_flow_struct flow ;
        ndpi_hw_struct *src = nullptr, *dst = nullptr;
        ndpi_protocol protocol = ndpi_detection_process_packet(
            ndpi_struct, &flow, packet, header.len, header.ts.tv_sec);

        // Convert the protocol information to a string and emit the signal
        QString info = QString::fromStdString(ndpi_get_proto_name(ndpi_struct, protocol.app_protocol));
        qDebug() << info;
        emit packetInfo(info);

        // Check if the thread should stop
        if (isInterruptionRequested()) {
            break;
        }
    }

    pcap_close(handle);
}
