#!/usr/bin/env python3
"""
ESP32 Serial Monitor and Debug Output Capture
Connects to ESP32 device via serial port, captures output to console and file.
Usage: python serial_monitor.py [--port PORT] [--baud BAUD] [--output FILE] [--timeout SECONDS]
"""

import serial
import sys
import argparse
from datetime import datetime
import os


def get_available_ports():
    """List available serial ports on the system."""
    try:
        import serial.tools.list_ports
        ports = list(serial.tools.list_ports.comports())
        return ports
    except ImportError:
        print("pyserial not installed. Install with: pip install pyserial")
        return []


def list_ports():
    """Display available COM ports."""
    ports = get_available_ports()
    if not ports:
        print("No serial ports found.")
        return None
    
    print("\nAvailable COM Ports:")
    print("-" * 60)
    for idx, port in enumerate(ports, 1):
        print(f"{idx}. {port.device:15} - {port.description}")
    print("-" * 60)
    
    return ports


def select_port_interactive(ports):
    """Allow user to select a port interactively."""
    if not ports:
        return None
    
    while True:
        try:
            choice = input(f"\nSelect port (1-{len(ports)}) or enter port name: ").strip()
            
            if choice.isdigit():
                idx = int(choice) - 1
                if 0 <= idx < len(ports):
                    return ports[idx].device
            else:
                # Check if user entered a port name like COM3 or /dev/ttyUSB0
                for port in ports:
                    if choice.lower() in port.device.lower():
                        return port.device
            
            print("Invalid selection. Try again.")
        except KeyboardInterrupt:
            print("\nCancelled.")
            return None


def connect_serial(port, baud=115200, timeout=5):
    """Establish serial connection."""
    try:
        ser = serial.Serial(
            port=port,
            baudrate=baud,
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            timeout=timeout
        )
        print(f"\n✓ Connected to {port} at {baud} baud")
        return ser
    except serial.SerialException as e:
        print(f"✗ Failed to connect to {port}: {e}")
        return None


def monitor_serial(ser, output_file=None, timeout_seconds=None):
    """
    Read from serial port and display/save output.
    
    Args:
        ser: Serial connection object
        output_file: Optional file to save output
        timeout_seconds: Optional timeout (None = no timeout)
    """
    output_handle = None
    start_time = datetime.now()
    
    if output_file:
        try:
            output_handle = open(output_file, 'a', encoding='utf-8', errors='replace')
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            output_handle.write(f"\n{'='*70}\n")
            output_handle.write(f"Session started: {timestamp}\n")
            output_handle.write(f"{'='*70}\n")
            output_handle.flush()
            print(f"✓ Logging output to: {output_file}")
        except IOError as e:
            print(f"✗ Cannot write to {output_file}: {e}")
            output_file = None
    
    print("\nListening to serial output... (Ctrl+C to stop)\n")
    print("-" * 70)
    
    try:
        while True:
            # Check timeout
            if timeout_seconds:
                elapsed = (datetime.now() - start_time).total_seconds()
                if elapsed > timeout_seconds:
                    print(f"\n[TIMEOUT: {timeout_seconds} seconds elapsed]")
                    break
            
            # Read from serial
            if ser.in_waiting:
                try:
                    line = ser.readline().decode('utf-8', errors='replace').rstrip('\n')
                    if line:
                        timestamp = datetime.now().strftime("%H:%M:%S.%f")[:-3]
                        formatted = f"[{timestamp}] {line}"
                        
                        # Print to console
                        print(formatted)
                        
                        # Write to file
                        if output_handle:
                            output_handle.write(formatted + '\n')
                            output_handle.flush()
                
                except UnicodeDecodeError as e:
                    print(f"[DECODE ERROR: {e}]")
    
    except KeyboardInterrupt:
        print("\n\n[STOPPED by user]")
    
    finally:
        if output_handle:
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            output_handle.write(f"\nSession ended: {timestamp}\n")
            output_handle.close()
        
        print("-" * 70)
        if output_file:
            print(f"✓ Output saved to: {output_file}")


def main():
    parser = argparse.ArgumentParser(
        description="ESP32 Serial Monitor - Capture and log debug output",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python serial_monitor.py                  # Interactive port selection
  python serial_monitor.py --port COM3      # Specify port
  python serial_monitor.py --port COM3 --output debug.log  # Save to file
  python serial_monitor.py --port /dev/ttyUSB0 --baud 230400 --timeout 30
        """
    )
    
    parser.add_argument(
        '--port',
        help='Serial port (e.g., COM3, /dev/ttyUSB0). If not specified, shows available ports.'
    )
    parser.add_argument(
        '--baud',
        type=int,
        default=115200,
        help='Baud rate (default: 115200)'
    )
    parser.add_argument(
        '--output',
        help='Output file to save debug messages (optional)'
    )
    parser.add_argument(
        '--timeout',
        type=int,
        help='Timeout in seconds (optional, no timeout if not specified)'
    )
    parser.add_argument(
        '--list',
        action='store_true',
        help='List available ports and exit'
    )
    
    args = parser.parse_args()
    
    # List ports and exit if requested
    if args.list:
        list_ports()
        return 0
    
    # Determine port
    port = args.port
    if not port:
        ports = list_ports()
        port = select_port_interactive(ports)
        if not port:
            return 1
    
    # Create output directory if needed
    if args.output and not os.path.exists(os.path.dirname(args.output) or '.'):
        try:
            os.makedirs(os.path.dirname(args.output) or '.', exist_ok=True)
        except OSError:
            pass
    
    # Connect and monitor
    ser = connect_serial(port, baud=args.baud)
    if not ser:
        return 1
    
    try:
        monitor_serial(ser, output_file=args.output, timeout_seconds=args.timeout)
    finally:
        ser.close()
        print("✓ Serial connection closed")
    
    return 0


if __name__ == '__main__':
    sys.exit(main())
