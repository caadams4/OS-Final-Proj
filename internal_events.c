#include "prototypes.h"


struct Request_devices *send_to_requests(struct Request_devices *request_device_head, struct Request_devices *req) {
    // SJF
    if (request_device_head == NULL) {
        request_device_head = req;
    } else {
        struct Request_devices *tmp_request_device_head = request_device_head;
        while (tmp_request_device_head->next != NULL) {    //hold_q_1_head->next removed
            tmp_request_device_head = tmp_request_device_head->next;
        }
        tmp_request_device_head->next = req; // add req to end of the Hold Queue 2 list
    }
    return request_device_head;
}

struct Release_devices *send_to_releases(struct Release_devices *release_device_head, struct Release_devices *req) {
    // SJF
    if (release_device_head == NULL) {
        release_device_head = req;
    } else {
        struct Release_devices *tmp_release_device_head = release_device_head;
        while (tmp_release_device_head->next != NULL) {    //hold_q_1_head->next removed
            tmp_release_device_head = tmp_release_device_head->next;
        }
        tmp_release_device_head->next = req; // add req to end of the Hold Queue 2 list
    }
    return release_device_head;
}

