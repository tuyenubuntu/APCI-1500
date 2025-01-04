def generate_mask(pin, value):
    """
    Tạo mã mask 16-bit dựa trên số thứ tự chân (pin) và giá trị (value).
    :param pin: Số thứ tự chân (1-based index, từ 1 đến 16).
    :param value: Giá trị (0 hoặc 1).
    :return: Mã mask dưới dạng số nguyên (16-bit).
    """
    if not (1 <= pin <= 16):
        raise ValueError("Số thứ tự chân phải nằm trong khoảng từ 1 đến 16.")
    if value not in (0, 1):
        raise ValueError("Giá trị phải là 0 hoặc 1.")

    # Tính mã mask và giới hạn trong 16-bit
    mask = (value << (pin - 1)) & 0xFFFF  # Đảm bảo kết quả là 16-bit
    return mask

# Nhập thông tin từ người dùng
try:
    pin = int(input("Nhập số thứ tự chân (1-16): "))
    value = int(input("Nhập giá trị (0 hoặc 1): "))
    mask = generate_mask(pin, value)
    print(f"Mã mask: {hex(mask)[2:].upper().zfill(4)} (hex), {bin(mask)[2:].zfill(16)} (binary), {mask} (decimal)")
except ValueError as e:
    print(f"Lỗi: {e}")
