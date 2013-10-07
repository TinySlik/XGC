/*
 * Copyright (c) 2011, Dongsheng Song <songdongsheng@live.cn>
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <pthread_clock.h>
#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>

#include "../src/misc.h"

__int64 timespec_diff_as_ms(struct timespec *__old, struct timespec *__new)
{
    return (__new->tv_sec - __old->tv_sec) * POW10_3
         + (__new->tv_nsec - __old->tv_nsec) / POW10_6;
}

int main(int argc, char *argv[])
{
    int rc;
    struct timespec tp, tp2, request = { 1, 0 }, remain;

    clock_gettime(CLOCK_REALTIME, &tp);
    rc = nanosleep(&request, &remain);
    clock_gettime(CLOCK_REALTIME, &tp2);

    if (rc != 0) {
        printf("remain: %d.%09d\n", (int) remain.tv_sec, (int) remain.tv_nsec);
    }

    printf("%d.%09d\n", (int) tp.tv_sec, (int) tp.tv_nsec);
    printf("%d.%09d\n", (int) tp2.tv_sec, (int) tp2.tv_nsec);
    printf("sleep %d ms\n", (int) timespec_diff_as_ms(&tp, &tp2));

    return 0;
}
