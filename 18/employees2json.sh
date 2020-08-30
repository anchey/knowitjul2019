#!/bin/sh
(echo '[' && tail -n +2 employees.csv | perl -p -e 's/(.*),(.*),([MF])/{"givenName":"\1","sn":"\2","sex":"\3"},/g' && echo 'null]') | jq . > employees.json
