FROM microsoft/iis:latest
MAINTAINET DNS7282
COPY Code.cpp
CMD ["cl /EHsc Code.cpp"] 
