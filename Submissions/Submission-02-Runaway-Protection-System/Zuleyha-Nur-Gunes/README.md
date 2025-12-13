Bu program, bir elektrikli araç gaz pedalı benzeri sistem için iki adet sensörden (ADC) gelen verileri okuyarak:

Sensör değerlerinin geçerli aralıkta olup olmadığını kontrol eder

Ham ADC değerlerini yüzde (%) cinsine dönüştürür

Sensörler arasında tutarlılık (plausibility) kontrolü yapar

Güvenli ise motora gönderilecek nihai torku hesaplar

Hata durumunda sistemi güvenli moda alır (tork = 0)

Bu yapı, otomotiv güvenlik mantığını (fail-safe) simüle etmek amacıyla hazırlanmıştır.

 Sistem Mantığı (Genel Akış)

Kullanıcıdan 2 adet ADC değeri alınır

Değerler izin verilen aralıkta mı kontrol edilir

ADC değerleri %0–%100 aralığına dönüştürülür

İki sensör arasındaki fark kontrol edilir

Hata yoksa tork hesaplanır, varsa sistem durdurulur

 Kullanılan Değerler

Sensör	ADC Aralığı	Yüzde Karşılığı

Sensör 1	1000 – 4000	%0 – %100

Sensör 2	500 – 2500	%0 – %100

 Fonksiyon Açıklamaları
main()

Kullanıcıdan ADC değerlerini alır

Sistem kontrollerini sırasıyla çağırır

Hata varsa torku sıfırlar ve sistemi kilitler

Hata yoksa ortalama torku hesaplar

check_range(PedalState *ps)

Sensör değerlerinin izin verilen aralıkta olup olmadığını kontrol eder

Değerler aralık dışındaysa:

status = "OutOfRange" yapılır

Sistem güvenli moda alınır

map_data(PedalState *ps)

Ham ADC değerlerini yüzdelik değere dönüştürür

Lineer dönüşüm kullanır

Sadece sistem durumu "OK" ise çalışır

check_plausibility(PedalState *ps)

İki sensörün yüzdelik değerleri arasındaki farkı kontrol eder

Fark %10’dan büyükse:

status = "Implausible" olur

Sensörler tutarsız kabul edilir

linear_map(...)

ADC değerlerini verilen aralıklara göre lineer olarak dönüştürür

Taşma (overflow) riskini önlemek için long long kullanır

Güvenli sınır kontrolleri içerir

 Güvenlik Mekanizması

Eğer sistem durumu:

"OutOfRange" veya

"Implausible"

olursa:

final_torque = 0 yapılır

Sistem sonsuz döngüye girerek kilitlenir

Bu projede main() fonksiyonu içerisinde, programın her aşamadan başarıyla geçip geçmediğini belirten bilgilendirici metinler (printf) bulunmaktadır.

Amaç:

Program akışının kolay takip edilebilmesini sağlamak

Test ve deneme aşamasında hangi adımda hata oluştuğunu hızlıca tespit etmek

Kodun okunabilirliğini ve anlaşılabilirliğini artırmak