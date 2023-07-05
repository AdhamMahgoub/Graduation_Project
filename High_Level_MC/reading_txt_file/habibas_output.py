def read_file_to_string(file_name):
    try:
        with open(file_name, 'r') as file:
            value = file.read()
            return value
    except FileNotFoundError:
        print(f"File '{file_name}' not found.")
        return None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None

# Replace 'readme.txt' with the actual path to your file
file_name = 'habibas_output.txt'
value = read_file_to_string(file_name)

#if value is not None:
#    print("File content:")
#    print(value)

split_strings = value.split("\n")    
product = split_strings[0]
price = split_strings[1]
