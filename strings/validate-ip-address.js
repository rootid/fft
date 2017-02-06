
const ip4 = /^(\.(([1-9]?|1\d|2[0-4])\d|25[0-5])){4}$/;
const ip6 = /^(:[0-9a-f]{1,4}){8}$/i;

var validIPAddress = function(IP) {
    return ip4.exec('.' + IP) ? 'IPv4' : ip6.exec(':' + IP) ? 'IPv6' : 'Neither';
};
