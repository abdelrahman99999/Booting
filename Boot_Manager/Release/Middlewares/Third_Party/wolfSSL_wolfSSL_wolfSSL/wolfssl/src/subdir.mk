################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/bio.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/conf.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/crl.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/dtls.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/dtls13.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/internal.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/keys.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ocsp.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/pk.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/quic.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/sniffer.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ssl.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ssl_misc.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/tls.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/tls13.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/wolfio.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/x509.c \
../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/x509_str.c 

OBJS += \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/bio.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/conf.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/crl.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/dtls.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/dtls13.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/internal.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/keys.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ocsp.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/pk.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/quic.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/sniffer.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ssl.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ssl_misc.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/tls.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/tls13.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/wolfio.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/x509.o \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/x509_str.o 

C_DEPS += \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/bio.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/conf.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/crl.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/dtls.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/dtls13.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/internal.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/keys.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ocsp.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/pk.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/quic.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/sniffer.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ssl.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ssl_misc.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/tls.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/tls13.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/wolfio.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/x509.d \
./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/x509_str.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/%.o Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/%.su: ../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/%.c Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F439xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/ -I../wolfSSL -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-wolfSSL_wolfSSL_wolfSSL-2f-wolfssl-2f-src

clean-Middlewares-2f-Third_Party-2f-wolfSSL_wolfSSL_wolfSSL-2f-wolfssl-2f-src:
	-$(RM) ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/bio.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/bio.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/bio.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/conf.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/conf.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/conf.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/crl.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/crl.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/crl.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/dtls.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/dtls.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/dtls.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/dtls13.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/dtls13.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/dtls13.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/internal.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/internal.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/internal.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/keys.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/keys.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/keys.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ocsp.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ocsp.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ocsp.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/pk.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/pk.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/pk.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/quic.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/quic.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/quic.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/sniffer.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/sniffer.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/sniffer.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ssl.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ssl.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ssl.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ssl_misc.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ssl_misc.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ssl_misc.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/tls.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/tls.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/tls.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/tls13.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/tls13.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/tls13.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/wolfio.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/wolfio.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/wolfio.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/x509.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/x509.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/x509.su ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/x509_str.d ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/x509_str.o ./Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/x509_str.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-wolfSSL_wolfSSL_wolfSSL-2f-wolfssl-2f-src

