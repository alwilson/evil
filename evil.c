#include <linux/version.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netfilter_ipv6.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <net/ip.h>

MODULE_LICENSE("GPL");

#define IP_EVIL 0x8000 /* Flag: "Evil" (RFC 3514) */

static unsigned int evil_hook(void*, struct sk_buff*,
	const struct nf_hook_state*);

static struct nf_hook_ops evil_nf_ops = {
	.hook     = evil_hook,
	.pf       = NFPROTO_IPV4,
	.hooknum  = NF_INET_LOCAL_OUT,
	.priority = NF_IP_PRI_FIRST,
};

static int evil_init(void)
{
	pr_debug("Becoming evil!\n");
	#if LINUX_VERSION_CODE > KERNEL_VERSION(4, 13, 0)
	return nf_register_net_hook(&init_net, &evil_nf_ops);
	#else
	return nf_register_hook(&evil_nf_ops);
	#endif
}

static void evil_exit(void)
{
	pr_debug("Repentance complete.\n");
	#if LINUX_VERSION_CODE > KERNEL_VERSION(4, 13, 0)
	nf_unregister_net_hook(&init_net, &evil_nf_ops);
	#else
	nf_unregister_hook(&evil_nf_ops);
	#endif
}

static unsigned int evil_hook(void *priv, struct sk_buff *skb,
	const struct nf_hook_state *state)
{
	struct iphdr *ip_header;

	ip_header = ip_hdr(skb);
	ip_header->frag_off |= htons(IP_EVIL);
	ip_send_check(ip_header);

	return NF_ACCEPT;
}

module_init(evil_init);
module_exit(evil_exit);
