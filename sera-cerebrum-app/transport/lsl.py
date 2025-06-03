from pylsl import StreamInlet, resolve_stream;

# resolve_stream is used to find the EEG stream from the LSL network.
streams = resolve_stream('name', 'EEG');

# Create a StreamInlet to read data from the EEG stream.
inlet = StreamInlet(streams[0]);

def read_eeg_data():
    """
        Reads EEG data from the LSL stream and returns the sample and timestamp.
        Returns:
            tuple: (sample, timestamp)
    """
    sample, timestamp = inlet.pull_sample()
    print(f"Timestamp: {timestamp}, Sample: {sample}")
    return sample, timestamp;



