# CGSS-Rijndael

Rijndael 256-CBC Implementation with mcrypt, for developing API client of Idolmaster Cinderella Girls Starlight Stage 

# Requirements

gcc >= 4.7
libmcrypt-dev

# Installation
<pre><code>python3 setup.py install</code></pre>
Currently, the module is only tested on Python 3.5.

# Usage
Import the module with:
<pre><code>import cgss-rijndael</code></pre>

Encrypt plaintext with:
<pre><code>cgss-rijndael.encrypt(Key, IV, plaintext)</code></pre>

Decrypt ciphertext with:
<pre><code>cgss-rijndael.decrypt(Key, IV, ciphertext)</code></pre>

Every key and IV must be 32 bytes long.

# License
Distributed with MIT License.