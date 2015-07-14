#!/bin/bash

( echo `date` `hostname` `id` $_CONDOR_SLOT ) | nc xrootd 5002

date
echo Has $# args: $@

echo

hostname
whoami
id

echo

uname -a

echo

env | sort

echo

sleep_time=5

echo Now sleeping for ${sleep_time}s ...

sleep ${sleep_time}

echo Over and out
date
