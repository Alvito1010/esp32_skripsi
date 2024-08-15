#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "memilah-1"                         //change this
 
const char WIFI_SSID[] = "iPhone vito";               //change this
const char WIFI_PASSWORD[] = "12345678";           //change this
const char AWS_IOT_ENDPOINT[] = "a3d6ocbe64cfcw-ats.iot.ap-southeast-1.amazonaws.com";       //change this
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAOq5NaCH3GjA2dB5mbhc4aQ+qOJcMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNDA1MTkxODUz
NTlaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDKpHl3zLg0Gh4wOYZo
4A4Qd6UMHt5blRZVrbqctw0FIrttfLH5Yk0W0wbSUZAgBMsGPiz0/c6FB4d3eNdu
uks1TNFq7CAci2IfgLkM3meoFe3kKS3cV6C4rNRk0r+lpyDEFBZBGxU5cfQVZ9hY
WcRyFHWP7G7L7bflDutWp+HXYFsS5xGVIUX6ZlpUaelgnBJKwdmm2gk23dUAhQnV
LhNwglc+a0klU6q0BHr7bhpXkz5dDGg9XIcUEBwh5pfmSjp7/9W+cRC4ViCZEzAN
WMZWNkpdYwmsgtFWcEb6YeS5rAkOX1bNfXppMqOXqDXjRl64yHcFs+7C+7Ys88t2
zJCdAgMBAAGjYDBeMB8GA1UdIwQYMBaAFFTjGCkOMvQUdmRHMUQUeboraDFPMB0G
A1UdDgQWBBQYxONjo4QkS6NPNaduhH1wljh/xzAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAXNxfVjeVWUVVphf47fyRWxWW
jaGRT1OT2V2iwuvitlQlhxPxIkkyhH3keI7c8z7rdxu5v+0YdUkZtbQkcKpu4euI
SxSwGdvnJKr8kAxOtp9VF4RZyBUeO0EHdOWcUGDMzOHR6A96sKnYq4ZmU/V7efqs
YFIDGeLGma0OO9nhyUpZH0UGwzXEBPQwwVIs1Q8or3KXY0WVsJmvi02SUCL2H/Gc
ywBTAclbAf2a8/TK2yfEqT3RO7jJp+TDkezGgLwL3ni74LuEtgmnQ37z+z42Y9fa
iqje2sgDQHpeIboHdAFsQKovThoHQkRYIcti/XFVLfhSfEdcOI6hkCotLlskiw==
-----END CERTIFICATE-----

 
 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAyqR5d8y4NBoeMDmGaOAOEHelDB7eW5UWVa26nLcNBSK7bXyx
+WJNFtMG0lGQIATLBj4s9P3OhQeHd3jXbrpLNUzRauwgHItiH4C5DN5nqBXt5Ckt
3FeguKzUZNK/pacgxBQWQRsVOXH0FWfYWFnEchR1j+xuy+235Q7rVqfh12BbEucR
lSFF+mZaVGnpYJwSSsHZptoJNt3VAIUJ1S4TcIJXPmtJJVOqtAR6+24aV5M+XQxo
PVyHFBAcIeaX5ko6e//VvnEQuFYgmRMwDVjGVjZKXWMJrILRVnBG+mHkuawJDl9W
zX16aTKjl6g140ZeuMh3BbPuwvu2LPPLdsyQnQIDAQABAoIBAHWAE1LM6Q6FCnYq
FO7g5CbWSWSSzZpLA21g1DEkzy7oKcfdoxEY19xhNrZjRu/Z96NCEC1qsgJfEETN
VBXHfe6FAXU/P4ttotLjf+mfWHmVZaCD5Cy8vtv2kx13OlsiYpRvlUvhGVh64+45
jbAFNSx1AooWrVQgHh56nSldJU4Nb6GRFk2Okn/9c1Ze9ExFzEligIGZ1Vao61AM
ZQ2J1iMGTfoBmVpO5fkokMsiWQIqAAxOJ8uW33j1Puq2PmcsSjmXoKdIj2oa+zHs
w2NVMw1HuFB8CAAbRTJC94RmLFMMGVeveNovjqqtiZ9kFMBq9zOW6VDvQeaFZFwA
Pu86+cECgYEA8ATw5LhMaYKTtqX+zy8chxXau4TE4ve2238C7jel0uE/b0XCqa0t
OCGdhg11AFL1lsJT6Ao0Cchym/GEX5tynBLWeCSLE/tr0Aipg77qse+QKTTdEdkh
j2rNTG949y62Igx7EeiZm5IXAEKe+jb6Mc2TXQklRW37MRTr+ec2vdECgYEA2CJ0
2jTF0xf0I3vZ2vYkDKMP6mpBx7wU+y78bnoOxagmfaonBvxNOM36RIntB1BIMSNY
e3/WTTy1ejUGLswueonxdNYmUVUe7snuQxKA31VBpDSLwiIwuXqs1f5mCwjRnbbE
AOxnzWQGLgHEIli3uN6HPE3dbXpvinsFkakQXQ0CgYEAhuQ//ksVpracDap86jOv
9Ltzkq+rd2OAgRuAqiDcMQgmfoLWREXvg/xga1ZkyynUnEXaoi4Z0OW2g63Yl2Ll
ppFvt1XSVAiZLvGvUzuY6yeX/ZCYLc+57MA5YRvFACZgdgJNqGLw8V3JT3whnL4J
HrRKfZ8GM178LTl05Z3sRgECgYAfpLPM+qr34+rngwt7Rkwy2XDMFjB5SK0dtVxZ
5F7jS2IPReke2bOInIeGn1bnmjZnk1AyDJ5YgonjUX4NPfGUGTwTqgLEJ502wrOy
eDQL/pR0sQjBLHZLwY0qa2uPNARUfdymcfYkmP9anwGTMb/8PgA4sQG5NJK+CJLh
J4pwxQKBgQDshHKJdfSiS73cj6vUYxU5Fen7ns4nnGqXo7R/Kkizv3oy9jRJpiCW
zaJcn6tsyzCX03up75W3IZiJzOOHfa2MBgrQRdMWt7jxzwdr5ezfE+yv+u5qrn/4
x70VJnJ6W7bEZ03QTIpXAWGqDD88qmVzmPAwa2Ba9tYJhx066S0bcA==
-----END RSA PRIVATE KEY-----

 
 
)KEY";