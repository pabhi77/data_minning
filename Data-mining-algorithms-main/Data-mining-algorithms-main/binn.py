import pandas as pd

def equal_width_binning(data, column_name, num_bins):
    """
    Performs equal-width binning on the specified column in the dataframe.

    Parameters:
        data (pd.DataFrame): The input dataframe.
        column_name (str): The name of the column to be binned.
        num_bins (int): The number of bins to create.

    Returns:
        pd.DataFrame: A new dataframe with the binned column.
    """
    # Create bins using pandas cut function with equal width
    data['equal_width_' + column_name] = pd.cut(data[column_name], bins=num_bins, labels=False, duplicates='drop')

    return data

def equal_frequency_binning(data, column_name, num_bins):
    """
    Performs equal-frequency binning on the specified column in the dataframe.

    Parameters:
        data (pd.DataFrame): The input dataframe.
        column_name (str): The name of the column to be binned.
        num_bins (int): The number of bins to create.

    Returns:
        pd.DataFrame: A new dataframe with the binned column.
    """
    # Create bins using pandas qcut function with equal frequency
    data['equal_frequency_' + column_name] = pd.qcut(data[column_name], q=num_bins, labels=False, duplicates='drop')

    return data

def main():
    # Load data from CSV file
    input_file = 'input.csv'
    output_file = 'output_data.csv'
    
    # Assuming your CSV has a header. If not, set header=None in the read_csv function.
    data = pd.read_csv(input_file)

    # Specify the column to be binned and the number of bins
    column_to_bin = 'YourColumnName'  # Replace with the actual column name
    number_of_bins = 5

    # Choose binning method (equal_width or equal_frequency)
    binning_method = 'equal_width'  # Change to 'equal_frequency' for equal-frequency binning

    # Apply the selected binning method
    if binning_method == 'equal_width':
        data = equal_width_binning(data, column_to_bin, number_of_bins)
    elif binning_method == 'equal_frequency':
        data = equal_frequency_binning(data, column_to_bin, number_of_bins)
    else:
        print("Invalid binning method. Choose 'equal_width' or 'equal_frequency'.")

    # Save the results to a new CSV file
    data.to_csv(output_file, index=False)

if __name__ == "__main__":
    main()
