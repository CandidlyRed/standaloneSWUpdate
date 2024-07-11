Standalone test for SWUpdate

Takes input URL and target description (test.json), feeds into SWUpdate API and incrementally calculate its sha256 hash

- When data is fully downloaded (or length in metadata han reached), sha256 should be checked against rawHashes.sha256 property. If match, continue, else interrupts bee

- Add a verification step before successful installation and parition switches ^

- Defining the hash is a seperate problem