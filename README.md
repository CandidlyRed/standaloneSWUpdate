Standalone test for SWUpdate

Takes input URL and target description (test.json), feeds into SWUpdate API and incrementally calculate its sha256 hash

- When data is fully downloaded (or length in metadata han reached), sha256 should be checked against rawHashes.sha256 property. If match, continue, else interrupts bee

- Add a verification step before successful installation. Partition is handled automatically

TODO:

- Curl from url and use that as the file to install. This is libcurl and it's incremental
- Generate hash incrementally. Combined with above
- Match data with target description. Reject/accept based on hash