def atoh( szBuf, length, byflag ):
    i=0
    tempvalue=0
    value=0
    if 8  <= length:
        length=8 
    
    while i<length:
        if 1==byflag:
            j=i
        elif 0 == byflag:
            j=length-1

        if szBuf[j] >= 'A' and szBuf[j]  <= 'F':
            tempvalue = int ( szBuf[j],  16 ) - int( 'A' , 16) + 10
        if szBuf[j]  >= 'a' and szBuf[j] <= 'f':
            tempvalue = int ( szBuf[j], 16 ) - int( 'a',  16 ) + 10
        if szBuf[j]  >= '0' and szBuf[j] <= '9':
            tempvalue = int ( szBuf[j], 16 ) - int( '0',  16 )

        value = value*16+tempvalue 
        i+=1

    return value

buf = "0a0b0c0z050607"
print("value = %x" %atoh(buf, 2, 1))
input()
