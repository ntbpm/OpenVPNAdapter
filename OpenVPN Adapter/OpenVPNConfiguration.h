//
//  OpenVPNConfiguration.h
//  OpenVPN Adapter
//
//  Created by Sergey Abramchuk on 21.04.17.
//
//

#import <Foundation/Foundation.h>

/**
 Transport protocol options
 */
typedef NS_ENUM(NSInteger, OpenVPNTransportProtocol) {
    ///
    OpenVPNTransportProtocolUDP,
    ///
    OpenVPNTransportProtocolTCP,
    ///
    OpenVPNTransportProtocolAdaptive,
    /// Use a transport protocol specified in the profile
    OpenVPNTransportProtocolDefault
};

/**
 IPv6 preference options
 */
typedef NS_ENUM(NSInteger, OpenVPNIPv6Preference) {
    /// Request combined IPv4/IPv6 tunnel
    OpenVPNIPv6PreferenceEnabled,
    /// Disable IPv6, so tunnel will be IPv4-only
    OpenVPNIPv6PreferenceDisabled,
    /// Leave decision to server
    OpenVPNIPv6PreferenceDefault
};

/**
 Compression mode options
 */
typedef NS_ENUM(NSInteger, OpenVPNCompressionMode) {
    /// Allow compression on both uplink and downlink
    OpenVPNCompressionModeEnabled,
    /// Support compression stubs only
    OpenVPNCompressionModeDisabled,
    /// Allow compression on downlink only (i.e. server -> client)
    OpenVPNCompressionModeAsym,
    /// Default behavior (support compression stubs only)
    OpenVPNCompressionModeDefault
};

/**
 Minimum TLS version options
 */
typedef NS_ENUM(NSInteger, OpenVPNMinTLSVersion) {
    /// Don't specify a minimum, and disable any minimum specified in profile
    OpenVPNMinTLSVersionDisabled,
    /// Use TLS 1.0 minimum (overrides profile)
    OpenVPNMinTLSVersion10,
    /// Use TLS 1.1 minimum (overrides profile)
    OpenVPNMinTLSVersion11,
    /// Use TLS 1.2 minimum (overrides profile)
    OpenVPNMinTLSVersion12,
    /// Use profile minimum
    OpenVPNMinTLSVersionDefault
};

/**
 Options of the tls-cert-profile setting
 */
typedef NS_ENUM(NSInteger, OpenVPNTLSCertProfile) {
    /// Allow 1024-bit RSA certs signed with SHA1
    OpenVPNTLSCertProfileLegacy,
    /// Require at least 2048-bit RSA certs signed with SHA256 or higher
    OpenVPNTLSCertProfilePreferred,
    /// Require NSA Suite-B
    OpenVPNTLSCertProfileSuiteB,
    /// Use legacy as the default if profile doesn't specify tls-cert-profile
    OpenVPNTLSCertProfileLegacyDefault,
    /// Use preferred as the default if profile doesn't specify tls-cert-profile
    OpenVPNTLSCertProfilePreferredDefault,
    /// Use profile default
    OpenVPNTLSCertProfileDefault
};

@interface OpenVPNConfiguration : NSObject

/**
 OpenVPN profile as a NSData
 */
@property (nullable, nonatomic) NSData *fileContent;

/**
 OpenVPN profile as series of key/value pairs (may be provided exclusively
 or in addition to file content).
 */
@property (nullable, nonatomic) NSDictionary<NSString *, NSString *> *settings;

/**
 Set to identity OpenVPN GUI version.
 Format should be "<gui_identifier><space><version>"
 Passed to server as IV_GUI_VER.
 */
@property (nullable, nonatomic) NSString *guiVersion;

/**
 Use a different server than that specified in "remote"
 option of profile
 */
@property (nullable, nonatomic) NSString *server;

/**
 Force a given transport protocol
 */
@property (nonatomic) OpenVPNTransportProtocol proto;

/**
 IPv6 preference
 */
@property (nonatomic) OpenVPNIPv6Preference ipv6;

/**
 Connection timeout in seconds, or 0 to retry indefinitely
 */
@property (nonatomic) NSInteger connectionTimeout;

/**
 Keep tun interface active during pauses or reconnections
 */
@property (nonatomic) BOOL tunPersist;

/**
 If true and a redirect-gateway profile doesn't also define
 DNS servers, use the standard Google DNS servers.
 */
@property (nonatomic) BOOL googleDNSFallback;

/**
 Enable autologin sessions
 */
@property (nonatomic) BOOL autologinSessions;

/**
 If YES, don't send client cert/key to peer
 */
@property (nonatomic) BOOL disableClientCert;

/**
 SSL library debug level
 */
@property (nonatomic) NSInteger sslDebugLevel;

/**
 Compression mode
 */
@property (nonatomic) OpenVPNCompressionMode compressionMode;

/**
 Private key password
 */
@property (nullable, nonatomic) NSString *privateKeyPassword;

/**
 Default key direction parameter for tls-auth (0, 1, 
 or -1 (bidirectional -- default)) if no key-direction 
 parameter defined in profile
 */
@property (nonatomic) NSInteger keyDirection;

/**
 If YES, force ciphersuite to be one of:
 1. TLS_DHE_RSA_WITH_AES_256_CBC_SHA, or
 2. TLS_DHE_RSA_WITH_AES_128_CBC_SHA
 and disable setting TLS minimum version.
 This is intended for compatibility with legacy systems.
 */
@property (nonatomic) BOOL forceCiphersuitesAESCBC;

/**
 Override the minimum TLS version
 */
@property (nonatomic) OpenVPNMinTLSVersion minTLSVersion;

/**
 Override or default the tls-cert-profile setting
 */
@property (nonatomic) OpenVPNTLSCertProfile tlsCertProfile;

/**
 Pass custom key/value pairs to OpenVPN server
 */
@property (nullable, nonatomic) NSDictionary<NSString *, NSString *> *peerInfo;

/**
 Pass through pushed "echo" directives via "ECHO" event
 */
@property (nonatomic) BOOL echo;

/**
 Pass through control channel INFO notifications via "INFO" event
 */
@property (nonatomic) BOOL info;

@end
