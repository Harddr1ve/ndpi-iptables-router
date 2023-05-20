#include "dpiworker.h"

DPIWorker::DPIWorker(QObject *parent) : QThread(parent) {}

DPIWorker::~DPIWorker() {
    if (ndpi_struct != nullptr)
        ndpi_exit_detection_module(ndpi_struct);
}

void DPIWorker::run()
{
    // Initialize nDPI
    struct ndpi_detection_module_struct *ndpi_struct;
    struct ndpi_flow_struct flow;
    struct ndpi_id_struct *src, *dst;

    ndpi_struct = ndpi_init_detection_module(0);
    if (ndpi_struct == NULL) {
        printf("ERROR: global structure initialization failed\n");
        return;
    }

    // Open the pcap file or device
    char errbuf[PCAP_ERRBUF_SIZE];
    const char* m_networkInterface = s_interface.toStdString().c_str();
    pcap_t *handle = pcap_open_live(m_networkInterface, MAX_PACKET_SIZE, 1, 1000, errbuf); //TODO: create interface selection from networkInterfaceModel
    if (handle == NULL) {
        printf("Couldn't open device: %s\n", errbuf);
        return;
    } else {
        qDebug() << "Device oppened";
    }

    // Process packets in a loop
    struct pcap_pkthdr header;
    const u_char *packet;
    while ((packet = pcap_next(handle, &header)) != NULL) {
        // Use nDPI to analyze the packet
        ndpi_protocol protocol = ndpi_detection_process_packet(
            ndpi_struct, &flow, packet, header.len, header.ts.tv_sec);

        // Convert the protocol information to a string and emit the signal
        QString info = QString::fromStdString(ndpi_get_proto_name(ndpi_struct, protocol.master_protocol));
        qDebug() << info << flow.dport;
        emit packetProcessed(info, flow.host_server_name);

        // Check if the thread should stop
        if (isInterruptionRequested()) {
            break;
        }
    }

    // Close the pcap handle and free the nDPI structures
    pcap_close(handle);
    ndpi_exit_detection_module(ndpi_struct);
}
