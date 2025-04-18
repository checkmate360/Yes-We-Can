#include "inc/hzl.h"
#include "inc/hzl_Client.h"
#include "inc/hzl_ClientOs.h"
#include "inc/hzl_Server.h"
#include "inc/hzl_ServerOs.h"


#include <stdio.h>
#include <stdlib.h>

int main() {
    hzl_Err_t err;
    hzl_ClientCtx_t* door_client;
    err = hzl_ClientNew(&door_client, "clients/Doors.hzl");
    if(err == HZL_OK) {
        printf("All good");
    }
}