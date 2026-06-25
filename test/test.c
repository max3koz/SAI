#include <stdio.h>
#include <sai.h>

/* test_profile_get_value and test_profile_get_next_value methods used by SAI
 * to read configuration values.
 * In the stub implementation they return dummy values and do nothing.
 * A real adapter would retrieve data from the SDK or configuration files.
 */
const char* test_profile_get_value(
    _In_ sai_switch_profile_id_t profile_id,
    _In_ const char* variable)
{
    return 0;
}

int test_profile_get_next_value(
    _In_ sai_switch_profile_id_t profile_id,
    _Out_ const char** variable,
    _Out_ const char** value)
{
    return -1;
}

/* Table of service methods passed to sai_api_initialize().
 * SAI uses these callbacks to access configuration profile data.
 */
const service_method_table_t test_services = {
test_profile_get_value,
test_profile_get_next_value
};

int main()
{
    sai_status_t              status;
    sai_switch_api_t          *switch_api;
    sai_object_id_t           vr_oid;
    sai_attribute_t           attrs[2];
    sai_switch_notification_t notifications;
    sai_object_id_t           port_list[64];
    sai_lag_api_t             *lag_api;
    sai_object_id_t           lag_oid1, lag_oid2;
    sai_object_id_t           lag_member_oid1, lag_member_oid2, lag_member_oid3, lag_member_oid4;
    sai_attribute_t           get_attr;

    /* 1. Initialize the SAI API.
     * The service method table is provided here.
     * In the stub implementation this only sets up internal structures.
     */
    status = sai_api_initialize(0, &test_services);

    /* 2. Query the SWITCH API.
     * sai_api_query returns a function table for switch operations.
     */
    status = sai_api_query(SAI_API_SWITCH, (void**)&switch_api);

    /* 3. Initialize the switch.
     * A real adapter would initialize the ASIC here.
     * The stub implementation only creates fake internal objects.
     */
    status = switch_api->initialize_switch(0, "HW_ID", 0, &notifications);

    /* 4. Prepare an attribute to request the port list.
     * We want to read SAI_SWITCH_ATTR_PORT_LIST.
     */
    attrs[0].id = SAI_SWITCH_ATTR_PORT_LIST;
    attrs[0].value.objlist.list = port_list; //where ports write
    attrs[0].value.objlist.count = 64;  //default max. q-ty ports

    /* 5. Call get_switch_attribute.
     * The stub implementation returns fake port object IDs.
     */
    status = switch_api->get_switch_attribute(1, attrs);

    /* 6.1. Print the list of ports.
     * In the stub these are just generated fake OIDs.
     */
    for (int32_t ii = 0; ii < attrs[0].value.objlist.count; ii++) {
        printf("Port #%d OID: 0x%lX\n", ii, attrs[0].value.objlist.list[ii]);
    }

    /* 7.1. LAG test create lag with 2 lag members and remove lag by oid

    printf("\n");
    printf("Testcase_01: LAG test create lag with 2 lag members and remove lag by oid\n");
    printf("Result:\n");
    status = sai_api_query(SAI_API_LAG, (void**)&lag_api);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to query LAG API, status=%d\n", status);
        return 1;
    }

    status = lag_api->create_lag(&lag_oid1, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create a LAG, status=%d\n", status);
        return 1;
    }

    status = lag_api->create_lag_member(&lag_member_oid1, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create LAG_MEMBER, status=%d\n", status);
        return 1;
    }

    status = lag_api->remove_lag_member(lag_member_oid1);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to remove LAG_MEMBER, status=%d\n", status);
        return 1;
    }

    status = lag_api->remove_lag(lag_oid1);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to remove LAG, status=%d\n", status);
        return 1;
    }
    */

    /* 7.2. Complicated LAG test to create/get/remove two lags with 2 lag members for each lag
     */
    printf("\n");
    printf("Testcase_02: Complicated LAG test to create/get/remove two lags with 2 lag members for each lag\n");
    printf("Result:\n");
    status = sai_api_query(SAI_API_LAG, (void**)&lag_api);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to query LAG API, status=%d\n", status);
        return 1;
    }

    status = lag_api->create_lag(&lag_oid1, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create a LAG, status=%d\n", status);
        return 1;
    }

    status = lag_api->create_lag_member(&lag_member_oid1, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create LAG_MEMBER, status=%d\n", status);
        return 1;
    }

    status = lag_api->create_lag_member(&lag_member_oid2, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create LAG_MEMBER, status=%d\n", status);
        return 1;
    }

    status = lag_api->create_lag(&lag_oid2, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create a LAG, status=%d\n", status);
        return 1;
    }

    status = lag_api->create_lag_member(&lag_member_oid3, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create LAG_MEMBER, status=%d\n", status);
        return 1;
    }

    status = lag_api->create_lag_member(&lag_member_oid4, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to create LAG_MEMBER, status=%d\n", status);
        return 1;
    }

    get_attr.id = SAI_LAG_ATTR_PORT_LIST;
    status = lag_api->get_lag_attribute(lag_oid1, 1, &get_attr);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to get LAG#1 PORT_LIST, status=%d\n", status);
        return 1;
    }

    get_attr.id = SAI_LAG_ATTR_PORT_LIST;
    status = lag_api->get_lag_attribute(lag_oid2, 1, &get_attr);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to get LAG#2 PORT_LIST, status=%d\n", status);
        return 1;
    }

    get_attr.id = SAI_LAG_MEMBER_ATTR_LAG_ID;
    status = lag_api->get_lag_member_attribute(lag_member_oid1, 1, &get_attr);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to get LAG_MEMBER#1 LAG_ID, status=%d\n", status);
        return 1;
    }

    get_attr.id = SAI_LAG_MEMBER_ATTR_PORT_ID;
    status = lag_api->get_lag_member_attribute(lag_member_oid3, 1, &get_attr);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to get LAG_MEMBER#3 PORT_ID, status=%d\n", status);
        return 1;
    }

/* Remove LAG_MEMBER#2 */
    status = lag_api->remove_lag_member(lag_member_oid2);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to remove LAG_MEMBER#2, status=%d\n", status);
        return 1;
    }

    /* Get LAG#1 PORT_LIST again */
    get_attr.id = SAI_LAG_ATTR_PORT_LIST;
    status = lag_api->get_lag_attribute(lag_oid1, 1, &get_attr);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to get LAG#1 PORT_LIST after removal, status=%d\n", status);
        return 1;
    }

    /* Remove LAG_MEMBER#3 */
    status = lag_api->remove_lag_member(lag_member_oid3);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to remove LAG_MEMBER#3, status=%d\n", status);
        return 1;
    }

    /* Get LAG#2 PORT_LIST again */
    get_attr.id = SAI_LAG_ATTR_PORT_LIST;
    status = lag_api->get_lag_attribute(lag_oid2, 1, &get_attr);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to get LAG#2 PORT_LIST after removal, status=%d\n", status);
        return 1;
    }

    /* Remove remaining members */
    status = lag_api->remove_lag_member(lag_member_oid1);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to remove LAG_MEMBER#1, status=%d\n", status);
        return 1;
    }

    status = lag_api->remove_lag_member(lag_member_oid4);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to remove LAG_MEMBER#4, status=%d\n", status);
        return 1;
    }

    /* Remove LAGs */
    status = lag_api->remove_lag(lag_oid2);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to remove LAG#2, status=%d\n", status);
        return 1;
    }

    status = lag_api->remove_lag(lag_oid1);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Failed to remove LAG#1, status=%d\n", status);
        return 1;
    }

    /* 8 Shut down the switch.
     * A real adapter would power down or deinitialize the ASIC.
     * The stub only clears internal structures.
     */
    switch_api->shutdown_switch(0);

    /* 9. Uninitialize the SAI API.
     */
    status = sai_api_uninitialize();

    return 0;
}