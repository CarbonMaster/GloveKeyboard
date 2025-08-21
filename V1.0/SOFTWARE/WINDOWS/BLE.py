import bluetooth

def main():
    print("Szukanie urządzeń Bluetooth...")
    nearby_devices = bluetooth.discover_devices(lookup_names=True)
    
    if len(nearby_devices) == 0:
        print("Nie znaleziono żadnych urządzeń Bluetooth w zasięgu.")
    else:
        print("Znalezione urządzenia Bluetooth:")
        for addr, name in nearby_devices:
            print(f"Adres MAC: {addr}, Nazwa: {name}")

if __name__ == "__main__":
    main()
