import socket
import json
import random

# Define the server address and port
SERVER_ADDRESS = "127.0.0.1"  # Localhost
SERVER_PORT = 65432           # Port for 2D simulation

def main():
    # Create a TCP socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Connect to the simulation server
        client_socket.connect((SERVER_ADDRESS, SERVER_PORT))
        print(f"Connected to 2D simulation server at {SERVER_ADDRESS}:{SERVER_PORT}")

        # Basic interaction loop
        for step in range(10):  # Simulate 10 steps
            # Generate random thrust direction and magnitude
            thrust_magnitude = random.uniform(10, 50)  # Random thrust between 10-50 kN
            thrust_direction = [random.uniform(-1, 1), random.uniform(-1, 1)]  # Random 2D unit vector
            direction_magnitude = (thrust_direction[0] ** 2 + thrust_direction[1] ** 2) ** 0.5
            thrust_direction = [d / direction_magnitude for d in thrust_direction]  # Normalize direction

            # Send thrust parameters to the simulation
            data_to_send = {
                "thrust_magnitude": thrust_magnitude,
                "thrust_direction": thrust_direction
            }
            client_socket.sendall(json.dumps(data_to_send).encode("utf-8"))
            print(f"Step {step}: Sent {data_to_send}")

            # Wait for response (state feedback) from the simulation
            response = client_socket.recv(1024).decode("utf-8")
            received_data = json.loads(response)
            print(f"Step {step}: Received {received_data}")

    except Exception as e:
        print(f"Error: {e}")
    finally:
        # Close the connection
        client_socket.close()
        print("Connection closed.")

if __name__ == "__main__":
    main()
