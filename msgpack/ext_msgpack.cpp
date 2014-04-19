#include "hphp/runtime/base/base-includes.h"
#include "hphp/runtime/ext/extension.h"
#include "hphp/runtime/base/complex-types.h"

#include <msgpack.hpp>
#include <iostream>

namespace HPHP {

	String php_msgpack_serial_recursive(const Variant& data);
	bool is_need_recursive(const std::string& data);

	class MsgpackException : public std::exception
	{
	public:
		MsgpackException(const char* msg) : error_msg(msg){}
		virtual ~MsgpackException() throw(){}
		virtual const char* what() const throw(){
			return error_msg.c_str(); 
		}

	private:
		std::string error_msg;
	};

	String php_msgpack_serialize(const Variant& data)
	{
		if (data.isString())
		{
			msgpack::sbuffer sbuf;
			std::string s = data.toString().toCppString();
			msgpack::pack(&sbuf, s);
			return String(sbuf.data(), sbuf.size(), CopyString);
		}
		else if (data.isDouble())
		{
			msgpack::sbuffer sbuf;
			msgpack::pack(&sbuf, data.toDouble());
			return String(sbuf.data(), sbuf.size(), CopyString);
		}
		else if (data.isArray())
		{
			return php_msgpack_serial_recursive(data);
		}
		else if (data.isBoolean())
		{
			msgpack::sbuffer sbuf;
			msgpack::pack(&sbuf, data.toBoolean());
			return String(sbuf.data(), sbuf.size(), CopyString);
		}
		else if (data.isObject())
		{
			/* code */
			return "";
		}
		else if (data.isNull())
		{
			msgpack::sbuffer sbuf;
			msgpack::type::nil v;
			msgpack::pack(&sbuf, v);
			return String(sbuf.data(), sbuf.size(), CopyString);
		}
		else if(data.isInteger())
		{
			msgpack::sbuffer sbuf;
			msgpack::pack(&sbuf, data.toInt32());
			return String(sbuf.data(), sbuf.size(), CopyString);
		}
		else
		{
			throw MsgpackException("unknown data type");
		}
		return "123";
	}

	String php_msgpack_serial_recursive(const Variant& data)
	{
		const Array data_arr = data.toArray();
		msgpack::sbuffer sbuf;
        msgpack::packer<msgpack::sbuffer> pk(&sbuf);
        pk.pack_map(data_arr.size());

		ArrayIter iter = data_arr.begin();

		Variant k;
		Variant v;
		for(; iter; ++iter) {
		    k = iter.first();
		    if (k.isString())
		    {
		    	std::string k_str = k.toString().toCppString();
		    	pk.pack(k_str);
		    }
		    else
		    {
		    	int k_int = k.toInt32();
		    	pk.pack(k_int);
		    }
		    
		    v = iter.second();
		    if (v.isArray()) {
		     	String serial_str = php_msgpack_serial_recursive(directRef(v));
		     	std::string v_str = serial_str.toCppString();
				pk.pack(v_str);
			}
			else if(v.isString()){
				std::string v_str = v.toString().toCppString();
				pk.pack(v_str);
			}
			else if(v.isDouble()){
				double v_dou = v.toDouble();
				pk.pack(v_dou);
			}
			else if(v.isBoolean()){
				bool v_boo = v.toBoolean();
				pk.pack(v_boo);
			}
			else if(v.isInteger()){
				int v_int = v.toInt32();
				pk.pack(v_int);
			}
			else if(v.isNull()){
				msgpack::type::nil v;
				pk.pack(v);
			}
			else {
				throw MsgpackException("unknown data type");
			}
		}

		return String(sbuf.data(), sbuf.size(), CopyString);
	}

	Variant php_msgpack_unserialize(const String& data)
	{
		msgpack::sbuffer sbuf;
		msgpack::unpacked msg;

		msgpack::unpack(&msg, data.c_str(), data.length());
		msgpack::object obj = msg.get();

		switch(obj.type)
		{
			case msgpack::type::object_type::RAW:
			{
				std::string s;
				obj >> s;
				return s;
			}
			break;
			case msgpack::type::object_type::BOOLEAN:
			{
				bool b;
				obj >> b;
				return b;
			}
			break;
			case msgpack::type::object_type::DOUBLE:
			{
				double d;
				obj >> d;
				return d;
			}
			break;
			case msgpack::type::object_type::POSITIVE_INTEGER:
			case msgpack::type::object_type::NEGATIVE_INTEGER:
			{
				int i;
				obj >> i;
				return i;
			}
			break;
			case msgpack::type::object_type::NIL:
			{
				return init_null_variant;
			}
			break;
			case msgpack::type::object_type::MAP:
			{
				Array a;
				msgpack::object_kv* pkv;
				msgpack::object_kv* pkv_end;
				msgpack::object pk, pv;
				if(obj.via.map.size > 0)
				{
					pkv = obj.via.map.ptr;
					pkv_end = obj.via.map.ptr + obj.via.map.size;

					do
					{
					 pk = pkv->key;
					 pv = pkv->val;

					 Variant k;
					 Variant v;
					 
					 if (pk.type == msgpack::type::object_type::RAW)
					 {
					 	std::string key;
					 	pk >> key;
					 	k = key;
					 }
					 else
					 {
					 	int key;
					 	pk >> key;
					 	k = key;
					 }

					 switch(pv.type){
				 	case msgpack::type::object_type::RAW:
					{
						std::string s;
						pv >> s;
						if (is_need_recursive(s))
					 	{
					 		v = php_msgpack_unserialize(String(s));
					 	}
					 	else
					 	{
					 		v = String(s);
					 	}
					}
					break;
				 	case msgpack::type::object_type::BOOLEAN:
					{
						bool b;
						pv >> b;
						v = b;
					}
					break;
					case msgpack::type::object_type::DOUBLE:
					{
						double d;
						pv >> d;
						v = d;
					}
					break;
					case msgpack::type::object_type::POSITIVE_INTEGER:
					case msgpack::type::object_type::NEGATIVE_INTEGER:
					{
						int i;
						pv >> i;
						v = i;
					}
					break;
					case msgpack::type::object_type::NIL:
					{
						v = init_null_variant;
					}
					break;
					default:
					 break;
					}

					a.add(k, v);

					 ++pkv;
					}
					while (pkv < pkv_end);
				}
				return a;
			}
			break;
			default:
				return "";
				break;
		}

		return "123";
	}

	bool is_need_recursive(const std::string& data)
	{
		msgpack::sbuffer sbuf;
		msgpack::unpacked msg;

		msgpack::unpack(&msg, data.c_str(), data.length());
		msgpack::object obj = msg.get();

		return obj.type == msgpack::type::object_type::MAP;
	}

	static String HHVM_FUNCTION(msgpack_serialize, const Variant& data)
	{
		return php_msgpack_serialize(data);
	}

	static Variant HHVM_FUNCTION(msgpack_unserialize, const String& data)
	{
		return php_msgpack_unserialize(data);
	}

	static String HHVM_FUNCTION(msgpack_pack, const Variant& data)
	{
		return php_msgpack_serialize(data);
	}

	static Variant HHVM_FUNCTION(msgpack_unpack, const String& data)
	{
		return php_msgpack_unserialize(data);
	}

	class msgpackExtension : public Extension {
	public:
    msgpackExtension() : Extension("msgpack") {}

    virtual void moduleInit() {
        HHVM_FE(msgpack_serialize);
        HHVM_FE(msgpack_unserialize);
        HHVM_FE(msgpack_pack);
        HHVM_FE(msgpack_unpack);

        loadSystemlib();
    }
} s_msgpack_extension;

// Uncomment for non-bundled module
HHVM_GET_MODULE(msgpack);

//////////////////////////////////////////////////////////////////////////////
} // namespace HPHP