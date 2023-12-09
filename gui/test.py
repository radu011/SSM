def invert_bytes(bytes_obj):
    return bytes(~b & 0xFF for b in bytes_obj)

data = str('a')
bData = bytes(data, 'utf-8')
invert_bytes = invert_bytes(bData)
print(invert_bytes)