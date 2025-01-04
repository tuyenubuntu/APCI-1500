def generate_mask(inputs):
    """
    Generate a hexadecimal mask based on input pins.

    Args:
        inputs (list): List of pin numbers (1-16).

    Returns:
        str: Hexadecimal mask as a string.
    """
    # Initialize the mask with 16 bits set to 0
    mask = 0

    for pin in inputs:
        if 1 <= pin <= 16:  # Ensure the pin is within the valid range
            # Set the bit corresponding to the pin (1-indexed)
            mask |= (1 << (pin - 1))
        else:
            raise ValueError(f"Invalid pin number: {pin}. Must be between 1 and 16.")

    # Convert the mask to a 4-digit hexadecimal string
    return f"{mask:04X}"

if __name__ == "__main__":
    # Prompt user for input
    user_input = input("Enter pin numbers (1-16) separated by spaces: ")

    try:
        # Convert input to a list of integers
        pin_numbers = list(map(int, user_input.split()))

        # Generate the mask
        mask = generate_mask(pin_numbers)

        # Display the result
        print(f"Hexadecimal mask: {mask}")
    except ValueError as e:
        print(f"Error: {e}")
