@echo off
cls
set SCRIPT_AES256_ENCRYPTION_KEY=8CDB6EA064AE310B004A810A0015E4B22DA98368DE992E7617F2FD7682B622F5
scons -j12 platform=windows tools=no target=debug bits=64