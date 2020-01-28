#pragma warning (disable: 4786)

//using namespace std;
#include "Container.h"

//Para que pueda tener las piezas información del contenedor
CONTAINER* BLOQUE_ARA::m_Container = NULL;

bool less_than(const std::map<int, int>& l, const std::map<int, int>& r)
{
	// same types, proceed to compare maps here

	if (l.size() != r.size())
		return (l.size() < r.size());  // differing sizes, they are not the same

	std::map<int, int>::const_iterator i, j;
	for (i = l.begin(), j = r.begin(); i != l.end(); ++i, ++j)
	{
		if (i->first != j->first)
			return ((i->first) < (j->first));
		if (i->second != j->second)
			return (i->second < j->second);
	}

	return false; //they are equal
}

bool PIECE::is_valid_orientation(int orienta)
{
	if ((orienta ==0 || orienta ==1) && m_Rotate_x == true)
		return true;
	if ((orienta ==2 || orienta ==3) && m_Rotate_y == true)
		return true;
	if ((orienta ==4 || orienta ==5) && m_Rotate_z == true)
		return true;
	return false;
}




//};

//Para la creación la x,y,z si es posible rotarla en cada dirección y la cantidad
BLOQUE_ARA::BLOQUE_ARA(int id, int x,  int y, int z, CONTAINER* a, int idpieza, int tipo)
{
	m_Id = id;

	m_x =  x; m_y = y; m_z = z;
	m_x2 = 0; m_y2 = 0; m_z2 = 0;
	m_volumen_ocupado = m_x * m_z * m_y;

	pack_area_l = m_x;
	pack_area_w = m_y;
	m_num_pieces_tipo[idpieza] = 1;
	m_num_pieces = m_num_pieces_tipo[idpieza];
	m_tipo = tipo;
	m_Container = a;
	m_Volumen = x * z * y;
	m_bloque1 = NULL;
	m_bloque2 = NULL;

}
//Para la creación la x,y,z si es posible rotarla en cada dirección y la cantidad
BLOQUE_ARA::BLOQUE_ARA(int id, int nx, int ny, int nz,  CONTAINER* a, PIECE* p)
{
	m_Id = id;

	m_x = nx*p->Get_x(); m_y =ny* p->Get_y(); m_z =nz* p->Get_z();
	m_x2 = 0; m_y2 = 0; m_z2 = 0;
	m_volumen_ocupado = m_x * m_z * m_y;

	pack_area_w = m_y;
	pack_area_l = m_x;
	m_num_pieces_tipo[p->Get_Id()] =nx*ny*nz;
	m_num_pieces = m_num_pieces_tipo[p->Get_Id()];

	m_Container = a;
	m_Volumen = m_x * m_z * m_y ;
	m_bloque1 = NULL;
	m_bloque2 = NULL;

}
BLOQUE_ARA::BLOQUE_ARA(int id,int x, int y, int z, int v_ocupado, std::map<int, int>& map_pieces)
{
	m_Id = id;
	m_x = x;
	m_y = y;
	m_z = z;
	m_x2 = 0; m_y2 = 0; m_z2 = 0;
	m_volumen_ocupado = v_ocupado;
	m_Volumen = x * y * z;
	m_num_pieces = 0;
	m_num_pieces_tipo = map_pieces;
	std::map<int, int>::iterator it_nb;
	for (it_nb = map_pieces.begin(); it_nb != map_pieces.end(); it_nb++) 
	{
		m_num_pieces += (*it_nb).second;
	}
//		sqr_volumes += (long64)((*it_nb).second * pow((*it_nb).first->volume, expon));

}


//Ver paper
void CONTAINER::Generar_Bloques(double min_fr, int max_bl, bool fsb)
{
	m_bloques_heterogeneos = 0;
	m_set_Bloques = Generar_bloques_sencillos();
//	m_set_Bloques = Generar_bloques_sencillos();
	clock_t begin_time = clock();
	std::set<BLOQUE_ARA*,compareBlocks> lista_P = m_set_Bloques;
	while (m_set_Bloques.size() < max_bl) {
		//  cout << B.size() << endl;
		std::set<BLOQUE_ARA*, compareBlocks> lista_N;
	//	set<Block*, compareBlocks> N;
		std::set<BLOQUE_ARA*, compareBlocks>::iterator itP = lista_P.begin();

		//set<Block*, compareBlocks>::iterator itP = P.begin();
		int new_elems = 0;
		for (; itP != lista_P.end() && m_set_Bloques.size() + new_elems < max_bl; itP++) {
			std::set<BLOQUE_ARA*,compareBlocks>::iterator itB = m_set_Bloques.begin();
			//set<Block*, compareBlocks>::iterator itB = B.begin();
			for (; itB != m_set_Bloques.end() && m_set_Bloques.size() + new_elems < max_bl; itB++) {

				// list<Block*> newB = Block::createBlocks(**itP, **itB, L, W, H, min_fr, fsb);
				std::list<BLOQUE_ARA*> newB = Crear_Bloques(**itP, **itB, m_X,  m_Y, m_Z, min_fr, fsb);

				//list<Block*>::iterator itNew = newB.begin();
				std::list<BLOQUE_ARA*>::iterator itNew= newB.begin();
				for (; itNew != newB.end(); itNew++) {
					if (feasible((*itNew)->Get_num_pieces_tipo()) /*&& (*itNew)->Get_volumen_ocupado()<=0.2*m_X*m_Y*m_Z*/) {
						int NoldSize = lista_N.size();
						if (m_set_Bloques.find(*itNew) == m_set_Bloques.end() && lista_N.find(*itNew) == lista_N.end()) {
							if (setlmax.find((*itNew)->Get_x()) == setlmax.end())
								setlmax.insert((*itNew)->Get_x());
							if (setwmax.find((*itNew)->Get_y()) == setwmax.end())
								setwmax.insert((*itNew)->Get_y());
							if (sethmax.find((*itNew)->Get_z()) == sethmax.end())
								sethmax.insert((*itNew)->Get_z());
							if ((*itNew)->Get_num_pieces_tipo().size() > 1)
								m_bloques_heterogeneos++;
							lista_N.insert(*itNew);
							new_elems++;
						}
						else delete* itNew;
						if (m_set_Bloques.size() + new_elems >= max_bl)
							break;
					}
					else delete* itNew;
				}
			}
//			if (get_time() > 20) return lista_B;

		}
		if (lista_N.size() == 0) break;
		printf("%.2f\n", (double(clock() - begin_time) / double(CLOCKS_PER_SEC)));

		m_set_Bloques.insert(lista_N.begin(), lista_N.end());
		lista_P = lista_N;
		printf("%.2f\n", (double(clock() - begin_time) / double(CLOCKS_PER_SEC)));
	}
	printf("%.2f\n", (double(clock() - begin_time) / double(CLOCKS_PER_SEC)));

}

/*
bool feasible(map<BoxType*, int>& nb_left_boxes) {
	map<BoxType*, int>::iterator it_nb;
	for (it_nb = nb_boxes.begin(); it_nb != nb_boxes.end(); it_nb++)
		if (nb_left_boxes[(*it_nb).first] < (*it_nb).second) return false;

	return true;
}*/
std::set< BLOQUE_ARA*,compareBlocks>  CONTAINER::Generar_bloques_sencillos()
{
	std::set< BLOQUE_ARA*,compareBlocks> lista_temp;
	for (int i = 0; i < m_Q;i++)
	{

		if (m_Pieces[i].Get_Rx())
		{
			//en x
			BLOQUE_ARA *B1= new BLOQUE_ARA(m_idBloques,m_Pieces[i].Get_y(), m_Pieces[i].Get_z(), m_Pieces[i].Get_x(),this,i,6);
			m_idBloques++;
			if (setlmax.find(B1->Get_x()) == setlmax.end())
				setlmax.insert(B1->Get_x());
			if (setwmax.find(B1->Get_y()) == setwmax.end())
				setwmax.insert(B1->Get_y());
			if (sethmax.find(B1->Get_z()) == sethmax.end())
				sethmax.insert(B1->Get_z());
			lista_temp.insert(B1);
			BLOQUE_ARA * B2 = new BLOQUE_ARA(m_idBloques, m_Pieces[i].Get_z(), m_Pieces[i].Get_y(), m_Pieces[i].Get_x(), this,i,5);
			m_idBloques++;
			if (setlmax.find(B2->Get_x()) == setlmax.end())
				setlmax.insert(B2->Get_x());
			if (setwmax.find(B2->Get_y()) == setwmax.end())
				setwmax.insert(B2->Get_y());
			if (sethmax.find(B2->Get_z()) == sethmax.end())
				sethmax.insert(B2->Get_z());
			lista_temp.insert(B2);
			
		}
		if (m_Pieces[i].Get_Ry())
		{
			//en x
			BLOQUE_ARA *B1 = new BLOQUE_ARA(m_idBloques, m_Pieces[i].Get_z(), m_Pieces[i].Get_x(), m_Pieces[i].Get_y(), this,i,4);
			m_idBloques++;
			if (setlmax.find(B1->Get_x()) == setlmax.end())
				setlmax.insert(B1->Get_x());
			if (setwmax.find(B1->Get_y()) == setwmax.end())
				setwmax.insert(B1->Get_y());
			if (sethmax.find(B1->Get_z()) == sethmax.end())
				sethmax.insert(B1->Get_z());
			lista_temp.insert(B1);
			BLOQUE_ARA *B2 =new BLOQUE_ARA(m_idBloques, m_Pieces[i].Get_x(), m_Pieces[i].Get_z(), m_Pieces[i].Get_y(), this,i,3);
			m_idBloques++;
			if (setlmax.find(B2->Get_x()) == setlmax.end())
				setlmax.insert(B2->Get_x());
			if (setwmax.find(B2->Get_y()) == setwmax.end())
				setwmax.insert(B2->Get_y());
			if (sethmax.find(B2->Get_z()) == sethmax.end())
				sethmax.insert(B2->Get_z());
			lista_temp.insert(B2);
		}
		if (m_Pieces[i].Get_Rz())
		{
			BLOQUE_ARA *B1 =new BLOQUE_ARA(m_idBloques, m_Pieces[i].Get_y(), m_Pieces[i].Get_x(), m_Pieces[i].Get_z(), this,i,2);
			m_idBloques++;
			if (setlmax.find(B1->Get_x()) == setlmax.end())
				setlmax.insert(B1->Get_x());
			if (setwmax.find(B1->Get_y()) == setwmax.end())
				setwmax.insert(B1->Get_y());
			if (sethmax.find(B1->Get_z()) == sethmax.end())
				sethmax.insert(B1->Get_z());
			lista_temp.insert(B1);
			BLOQUE_ARA *B2 =new BLOQUE_ARA(m_idBloques, m_Pieces[i].Get_x(), m_Pieces[i].Get_y(), m_Pieces[i].Get_z(), this,i,1);
			m_idBloques++;
			if (setlmax.find(B2->Get_x()) == setlmax.end())
				setlmax.insert(B2->Get_x());
			if (setwmax.find(B2->Get_y()) == setwmax.end())
				setwmax.insert(B2->Get_y());
			if (sethmax.find(B2->Get_z()) == sethmax.end())
				sethmax.insert(B2->Get_z());
			lista_temp.insert(B2);
		}
	}
	return lista_temp;
}


/*
set<Block*, compareBlocks> CLP::general_block_generator(double min_fr, int max_bl, bool fsb) {
	clock_t begin = clock();
	set<Block*, compareBlocks> B = single_box_block_generator();

	//set<Block*, compareBlocks>:: iterator it=B.begin();
	//for(;it!=B.end() ; it++)
		//(*it)->print();

	set<Block*, compareBlocks> P = B;
	while (B.size() < max_bl) {
		//  cout << B.size() << endl;
		set<Block*, compareBlocks> N;
		set<Block*, compareBlocks>::iterator itP = P.begin();
		int new_elems = 0;
		for (; itP != P.end() && B.size() + new_elems < max_bl; itP++) {
			set<Block*, compareBlocks>::iterator itB = B.begin();
			for (; itB != B.end() && B.size() + new_elems < max_bl; itB++) {

				list<Block*> newB = Block::createBlocks(**itP, **itB, L, W, H, min_fr, fsb);
				list<Block*>::iterator itNew = newB.begin();
				for (; itNew != newB.end(); itNew++) {
					if ((*itNew)->feasible(nb_boxes)) {
						int NoldSize = N.size();
						if (B.find(*itNew) == B.end() && N.find(*itNew) == N.end()) {
							N.insert(*itNew);
							new_elems++;
						}
						else delete* itNew;
						if (B.size() + new_elems >= max_bl)
							break;
					}
					else delete* itNew;
				}
			}
			if (get_time() > 20) return B;

		}
		if (N.size() == 0) break;
		B.insert(N.begin(), N.end());
		P = N;
	}
	return B;
}



*/
 

//Crea una lista de a lo mas 3 bloques juntando dos bloques (sin rotacion)
   //fsb=full supported blocks

// Crea una lista de a lo mas 3 bloques juntando dos bloques(sin rotacion)
std::list<BLOQUE_ARA*> CONTAINER::Crear_Bloques(BLOQUE_ARA& b1, BLOQUE_ARA& b2, int  maxL, int maxW,
	int  maxH, double min_fr, bool fsb)
{
//list<Block*> Block::createBlocks(Block& b1, Block& b2, long64 maxL, long64 maxW,
	//long64 maxH, double min_fr, bool fsb) {

	std::list<BLOQUE_ARA*> blocks;

	int volume = b1.Get_Volumen() + b2.Get_Volumen();
	int occupied_volume = b1.Get_volumen_ocupado() + b2.Get_volumen_ocupado();
	if (volume > occupied_volume)
		int kk = 9;
	int vol = 0;

//	map<BoxType*, int>* m_num_pieces_tipo = NULL;
	std::map<int, int>* m_num_pieces_tipo=NULL;
//	std::map<int, int> m_num_pieces_tipo;

//	map<BoxType*, int>::const_iterator it_nb;
	std::map<int, int>::const_iterator it_nb;

	for (int i = 0; i < 3; i++) {

		int ll = max(b1.Get_x(), b2.Get_x());
		int ww = max(b1.Get_y(), b2.Get_y());
		int hh = max(b1.Get_z(), b2.Get_z());

		int pack_area_l = 0;
		int pack_area_w = 0;

		switch (i) {
		case 0:
			if (fsb && (b1.Get_z() != b2.Get_z() || b1.Get_pack_area_l() != b1.Get_x() || b2.Get_pack_area_l() != b2.Get_x())) 
				continue;
			pack_area_l = b1.Get_pack_area_l() + b2.Get_pack_area_l();
			pack_area_w = min(b1.Get_pack_area_w(), b2.Get_pack_area_w());
			ll = (b1.Get_x() + b2.Get_x()); break;
		case 1:
			if (fsb && (b1.Get_z() != b2.Get_z() || b1.Get_pack_area_w() != b1.Get_y() || b2.Get_pack_area_w() != b2.Get_y())) continue;
			pack_area_l = min(b1.Get_pack_area_l(), b2.Get_pack_area_l());
			pack_area_w = b1.Get_pack_area_w() + b2.Get_pack_area_w();
			ww = (b1.Get_y() + b2.Get_y()); break;
		case 2:
			if (fsb && ((b1.Get_pack_area_w() < b2.Get_y() || b1.Get_pack_area_l() < b2.Get_x()) &&
				(b2.Get_pack_area_w() < b1.Get_y() || b2.Get_pack_area_l() < b1.Get_x()))) continue;
			pack_area_l = min(b1.Get_pack_area_l(), b2.Get_pack_area_l());
			pack_area_w = min(b1.Get_pack_area_w(), b2.Get_pack_area_w());
			hh = (b1.Get_z() + b2.Get_z());
		}

		if (ll > maxL || ww > maxW || hh > maxH) continue;

		int vol = ll * ww * hh;
		if ((double)occupied_volume / (double)vol >= min_fr) {
/*			if (occupied_volume < vol)
			{
				printf("OV %d Vol %d\n", occupied_volume, vol);
				int kk = 9;
			}*/
//			std::map<int, int> m_num_pieces_tipo;
			if (!m_num_pieces_tipo) {
				m_num_pieces_tipo = new map<int, int>();
				for (it_nb = b1.Get_num_pieces_tipo().begin(); it_nb != b1.Get_num_pieces_tipo().end(); it_nb++)
					(*m_num_pieces_tipo)[(*it_nb).first] += (*it_nb).second;

				for (it_nb = b2.Get_num_pieces_tipo().begin(); it_nb != b2.Get_num_pieces_tipo().end(); it_nb++)
					(*m_num_pieces_tipo)[(*it_nb).first] += (*it_nb).second;
			}
	
			//BLOQUE_ARA * new_block = new BLOQUE_ARA(ll, ww, hh, b1.Get_volumen_ocupado() + b2.Get_volumen_ocupado(), m_num_pieces_tipo);
			
			BLOQUE_ARA * new_block = new BLOQUE_ARA(m_idBloques++,ll, ww, hh,  b1.Get_volumen_ocupado() + b2.Get_volumen_ocupado(),*m_num_pieces_tipo);
		//	if (m_num_pieces_tipo.size() > 1)
			//	int kk = 9;
			new_block->Set_pack_area_w(pack_area_w);
			new_block->Set_pack_area_l(pack_area_l);

			//se ponen uno sobre otro
			if (fsb && i == 2) {
				if (b1.Get_pack_area_w() >= b2.Get_y() && b1.Get_pack_area_l() >= b2.Get_x()) {
					new_block->Set_bloque1(&b1);  //bloque inferior
					new_block->Set_bloque2(&b2);  //bloque superior
				}
				else {
					new_block->Set_bloque1(&b2);  //bloque inferior
					new_block->Set_bloque2(&b1);  //bloque superior
				}
			}
			else {
				new_block->Set_bloque1(&b1);  //bloque inferior
				new_block->Set_bloque2(&b2);  //bloque superior
			}


			//~ //ubicacion relativa del segundo bloque
			/*switch (i) {
			case 0: new_block->x2 = new_block->block1->l; break;
			case 1: new_block->y2 = new_block->block1->w; break;
			case 2: new_block->z2 = new_block->block1->h;
			}*/
			switch (i) {
			case 0: new_block->Set_x2(new_block->Get_bloque1().Get_x()); break;
			case 1: new_block->Set_y2(new_block->Get_bloque1().Get_y()); break;
			case 2: new_block->Set_z2(new_block->Get_bloque1().Get_z());;
			}
			if (b1.Get_tipo() < 0 || b2.Get_tipo() < 0 || b1.Get_tipo() > 6 || b2.Get_tipo() > 6)
				int kk = 9;
			if (b1.Get_num_pieces_tipo().size()==1 && b2.Get_num_pieces_tipo().size() == 1 && b1.Get_num_pieces_tipo().begin()->first == b2.Get_num_pieces_tipo().begin()->first && b1.Get_tipo() == b2.Get_tipo())
				new_block->Set_tipo(b1.Get_tipo());
			else
				new_block->Set_tipo(0);
			blocks.push_back(new_block);

		}
/*		else
		{
			printf("Hay perdida auiii");
		}*/
	}
	if (m_num_pieces_tipo) delete m_num_pieces_tipo;
//	if (blocks.size() > 0 )
//	{
//		list<BLOQUE_ARA*> ::iterator itl;
//		for (itl=blocks.begin();itl!=blocks.end(); itl++)
//		{
//			(*itl)->Print();
//
//		}
////		printf("Algo pasa");
//	}
	return blocks;

}

void BLOQUE_ARA::Print()
{
	printf("W %d L %d H %d Junta B1 %d %d %d B2 %d %d %d\n", m_z, m_x, m_y, m_bloque1->Get_z(), m_bloque1->Get_x(), m_bloque1->Get_y(), m_bloque2->Get_z(), m_bloque2->Get_x(), m_bloque2->Get_y());
}
//retorna si se puede crear el bloque con las cajas que quedan
bool CONTAINER::feasible(std::map<int, int> & nb_boxes) {
	std::map<int, int>::iterator it_nb;
	for (it_nb = nb_boxes.begin(); it_nb != nb_boxes.end(); it_nb++)
		if ((m_Pieces[(*it_nb).first].Get_q()- m_Pieces[(*it_nb).first].Get_Num()) < (*it_nb).second) return false;

	return true;
}

void CONTAINER::ColocarPiezasBloque(int xi, int yi, int zi, int x0, int y0, int z0, BLOQUE_ARA& Bloque, std::list<CONFIGURACAO>& lista, int orig)
{
	if (Bloque.Get_Num() > 1 && Bloque.Get_tipo()==0) {
		//	if (Bloque.Get_bloque1() == NULL) cout << "error" << endl;
		ColocarPiezasBloque(xi, yi, zi, x0, y0, z0, Bloque.Get_bloque1(), lista, orig);
		ColocarPiezasBloque(xi, yi, zi, x0 + Bloque.Get_x2(), y0 + Bloque.Get_y2(), z0 + Bloque.Get_z2(), Bloque.Get_bloque2(), lista, orig);

		//~ cout << "block " << id << ": (" << x0 << "," << y0 << "," << z0 << "); " << 
		 //~ ": (" << x0+l << "," << y0+w << "," << z0+h << "); " << endl;
	}
	else {
		//TODO Revisar que está bien los tres últimos parámetros
		if (Bloque.Get_Num() == 1)
		{
			CONFIGURACAO NuevaConfiguracao(this, (Bloque.Get_num_pieces_tipo().begin())->first, x0 + xi, y0 + yi, z0 + zi, x0 + Bloque.Get_x() + xi, y0 + Bloque.Get_y() + yi, z0 + Bloque.Get_z() + zi, Bloque.Get_tipo(), 1, orig);
			if (NuevaConfiguracao.Get_Tipo() == 0 || NuevaConfiguracao.Get_Tipo() > 6)
				int kl = 9;/*
			ORIG OrigActual(Espacio.Get_dx() - Eje_x * x, Espacio.Get_dy() - Eje_y * y, Espacio.Get_dz() - Eje_z * z);*/
			NuevaConfiguracao.Set_dx(1);
			NuevaConfiguracao.Set_dy(1);
			NuevaConfiguracao.Set_dz(1);
			InsertarConfiguracaoOrden(NuevaConfiguracao, lista);
		}
		else
		{
			CONFIGURACAO NuevaConfiguracao(this, (Bloque.Get_num_pieces_tipo().begin())->first, x0 + xi, y0 + yi, z0 + zi, x0 + Bloque.Get_x() + xi, y0 + Bloque.Get_y() + yi, z0 + Bloque.Get_z() + zi, Bloque.Get_tipo(), (Bloque.Get_num_pieces_tipo().begin())->second, orig);
			if (NuevaConfiguracao.Get_Tipo() == 0 || NuevaConfiguracao.Get_Tipo() > 6)
				int kl = 9;
			int x = m_Pieces[(Bloque.Get_num_pieces_tipo().begin())->first].Get_x();
			int y = m_Pieces[(Bloque.Get_num_pieces_tipo().begin())->first].Get_y();
			int z = m_Pieces[(Bloque.Get_num_pieces_tipo().begin())->first].Get_z();
			switch (Bloque.Get_tipo())
			{
			case 1:
			{
				NuevaConfiguracao.Set_dx((NuevaConfiguracao.Get_x2() - NuevaConfiguracao.Get_x1()) / x);
				NuevaConfiguracao.Set_dy((NuevaConfiguracao.Get_y2() - NuevaConfiguracao.Get_y1()) / y);
				NuevaConfiguracao.Set_dz((NuevaConfiguracao.Get_z2() - NuevaConfiguracao.Get_z1()) / z);
			}
			break;
			case 2:
			{
				NuevaConfiguracao.Set_dx((NuevaConfiguracao.Get_x2() - NuevaConfiguracao.Get_x1()) / y);
				NuevaConfiguracao.Set_dy((NuevaConfiguracao.Get_y2() - NuevaConfiguracao.Get_y1()) / x);
				NuevaConfiguracao.Set_dz((NuevaConfiguracao.Get_z2() - NuevaConfiguracao.Get_z1()) / z);
			}
			break;
			case 3:
			{
				NuevaConfiguracao.Set_dx((NuevaConfiguracao.Get_x2() - NuevaConfiguracao.Get_x1()) / x);
				NuevaConfiguracao.Set_dy((NuevaConfiguracao.Get_y2() - NuevaConfiguracao.Get_y1()) / z);
				NuevaConfiguracao.Set_dz((NuevaConfiguracao.Get_z2() - NuevaConfiguracao.Get_z1()) / y);
			}
			break;
			case 4:
			{
				NuevaConfiguracao.Set_dx((NuevaConfiguracao.Get_x2() - NuevaConfiguracao.Get_x1()) / z);
				NuevaConfiguracao.Set_dy((NuevaConfiguracao.Get_y2() - NuevaConfiguracao.Get_y1()) / x);
				NuevaConfiguracao.Set_dz((NuevaConfiguracao.Get_z2() - NuevaConfiguracao.Get_z1()) / y);
			}
			break;
			case 5:
			{
				NuevaConfiguracao.Set_dx((NuevaConfiguracao.Get_x2() - NuevaConfiguracao.Get_x1()) / z);
				NuevaConfiguracao.Set_dy((NuevaConfiguracao.Get_y2() - NuevaConfiguracao.Get_y1()) / y);
				NuevaConfiguracao.Set_dz((NuevaConfiguracao.Get_z2() - NuevaConfiguracao.Get_z1()) / x);
			}
			break;
			case 6:
			{
				NuevaConfiguracao.Set_dx((NuevaConfiguracao.Get_x2() - NuevaConfiguracao.Get_x1()) / y);
				NuevaConfiguracao.Set_dy((NuevaConfiguracao.Get_y2() - NuevaConfiguracao.Get_y1()) / z);
				NuevaConfiguracao.Set_dz((NuevaConfiguracao.Get_z2() - NuevaConfiguracao.Get_z1()) / x);
			}
			}

			/*lista.push_back(NuevaConfiguracao);*/
			InsertarConfiguracaoOrden(NuevaConfiguracao, lista);
		}
			//		myfile << nb_boxes.begin()->first->id;
			//	myfile << "	(" << x0 << "," << y0 << "," << z0 << ")	" <<
				//	"(" << x0 + l << "," << y0 + w << "," << z0 + h << ")" << endl;
		
		//		boxes.push_back(new Box(x0, y0, z0, x0 + l, y0 + w, z0 + h));
			//	calc += l * w * h;
	}


}


void CONTAINER::ActualizarListasAra(SPACE& E, CONFIGURACAO& C)
{
	BLOQUE_ARA& Bloque = BuscarPiezasBloqueAra(C.Get_Id());
	bool quitar_piezas = false;
	std::map<int, int>::iterator itm, itmfin = Bloque.Get_num_pieces_tipo().end();
	for (itm=(Bloque.Get_num_pieces_tipo().begin());itm!=itmfin;itm++)
	    m_Pieces[itm->first].Add_Num(itm->second);
	m_total_volumen_ocupado += Bloque.Get_volumen_ocupado();

	for (itm = (Bloque.Get_num_pieces_tipo().begin()); itm != itmfin; itm++)
	{
		if (m_Pieces[itm->first].Get_Num() == m_Pieces[itm->first].Get_q() &&
			(m_Pieces[itm->first].Get_x() == m_dimension_menor || m_Pieces[itm->first].Get_y() == m_dimension_menor || m_Pieces[itm->first].Get_z() == m_dimension_menor))
		{
			MinimaDimension();
			quitar_piezas = true;
		}
	}
	std::list< SPACE > lista_temp;
	if (m_full_supported == true)
	{
		SPACE Espacio(this, C.Get_x1(), C.Get_y1(), C.Get_z2(), Bloque.Get_pack_area_l(), Bloque.Get_pack_area_w(), m_Z - C.Get_z2()); //Espacio superior, solo si hay FS
		lista_temp.push_back(Espacio);
		/*JuntarSpacesBloques(m_Spaces, lista_temp, C);*/
	}
	
	ActualizarEspaciosElegido(E, C, lista_temp);
	if (m_juntar_spaces == true)
		JuntarSpacesBloques(m_Spaces, lista_temp, C);
	std::list< SPACE > ::iterator it;

	for (it = m_Spaces.begin(); it != m_Spaces.end(); it++)
	{
		if ((*it).Get_x1() == E.Get_x1() && (*it).Get_x2() == E.Get_x2() &&
			(*it).Get_y1() == E.Get_y1() && (*it).Get_y2() == E.Get_y2() &&
			(*it).Get_z1() == E.Get_z1() && (*it).Get_z2() == E.Get_z2())
		{
			m_Spaces.erase(it);
			break;
		}

	}
	//Primero miro con los que hay ya que
	std::list< SPACE > ::iterator itfin = m_Spaces.end();
	for (it = m_Spaces.begin(); it != m_Spaces.end();)
	{
		//Si se intersectan hacer los espacios
		if (!(C.Get_x2() <= (*it).Get_x1() || C.Get_x1() >= (*it).Get_x2())
			&& !(C.Get_y2() <= (*it).Get_y1() || C.Get_y1() >= (*it).Get_y2())
			&& !(C.Get_z2() <= (*it).Get_z1() || C.Get_z1() >= (*it).Get_z2()))
		{

			ActualizarEspaciosElegido((*it), C, lista_temp);
			it = m_Spaces.erase(it);
		}
		else
			++it;

	}
	if (m_juntar_spaces == true)
		JuntarSpacesBloques(m_Spaces, lista_temp, C);
	if (quitar_piezas == true)
	{
		if (m_multicontainer == false)
		{
			//Aqui pruebo si puede quitar alguno y es mas rapido
			if (m_eliminar_espacios == true)
			{
				std::list<SPACE> ::iterator itfin1 = m_Spaces.end();
				for (it = m_Spaces.begin(); it != itfin1;)
				{
					if (((m_dimension_menor > min(min((*it).Get_dx(), (*it).Get_dy()), (*it).Get_dz()))
						|| CabeAlguna((*it).Get_dx(), (*it).Get_dy(), (*it).Get_dz()) == false))
					{
						it = m_Spaces.erase(it);

					}
					else
						++it;
				}
			}
		}
		else
		{
			std::list<SPACE> ::iterator itfin2 = m_Spaces.end();
			for (it = m_Spaces.begin(); it != itfin2;)
			{
				if ((m_dimension_menor_x > (*it).Get_dx()) ||
					(m_dimension_menor_y > (*it).Get_dy()) ||
					(m_dimension_menor_z > (*it).Get_dz()) ||
					(m_menor_volumen > (*it).Get_Volumen()))
				{
					it = m_Spaces.erase(it);

				}
				else
					++it;
			}
		}
	}

	//Buscar inclusiones pero solamente con  los nuevos entres ssi
	EliminarInclusionesNuevos(lista_temp);
	//Buscar inclusiones de los nuevos con los antiguos esta función me debería colocar ya las
	//nuevas ordenadas
	//Aqui pruebo si puede quitar alguno y es mas rapido

	EliminarInclusionesListaAntigua(m_Spaces, lista_temp);

	//Esta función incluye los nuevos en la lista 
	//15-09-06 
//	m_Spaces.insert(m_Spaces.begin(),lista_temp.begin(),lista_temp.end());
	ColocarOrdenadosNuevos(m_Spaces, lista_temp);
	if (m_space_arriba == false)
		m_space_arriba = true;
	/*EliminarInclusionesNuevos(m_Spaces);*/
	//	EliminarInclusiones();
	//	}

}

void CONTAINER::ActualizarListasAraMov(SPACE& E, CONFIGURACAO& C, std::list<SPACE> &lista_espacios)
{
	BLOQUE_ARA& Bloque = BuscarPiezasBloqueAra(C.Get_Id());
	bool quitar_piezas = false;
	std::map<int, int>::iterator itm, itmfin = Bloque.Get_num_pieces_tipo().end();
	for (itm = (Bloque.Get_num_pieces_tipo().begin()); itm != itmfin; itm++)
		m_Pieces_Tabu[itm->first]+=itm->second;
	m_total_volumen_ocupado += Bloque.Get_volumen_ocupado();

	for (itm = (Bloque.Get_num_pieces_tipo().begin()); itm != itmfin; itm++)
	{
		if (m_Pieces_Tabu[itm->first] == m_Pieces[itm->first].Get_q() &&
			(m_Pieces[itm->first].Get_x() == m_dimension_menor || m_Pieces[itm->first].Get_y() == m_dimension_menor || m_Pieces[itm->first].Get_z() == m_dimension_menor))
		{
			MinimaDimensionMov();
			quitar_piezas = true;
		}
	}
	std::list< SPACE > lista_temp;
	if (m_full_supported == true)
	{
		SPACE Espacio(this, C.Get_x1(), C.Get_y1(), C.Get_z2(), Bloque.Get_pack_area_l(), Bloque.Get_pack_area_w(), m_Z - C.Get_z2()); //Espacio superior, solo si hay FS
		lista_temp.push_back(Espacio);
		/*JuntarSpacesBloques(lista_espacios, lista_temp, C);*/
	}

	ActualizarEspaciosElegidoMov(E, C, lista_temp, lista_espacios);
	if (m_juntar_spaces == true)
		JuntarSpacesBloques(lista_espacios, lista_temp, C);
	std::list< SPACE > ::iterator it;

	for (it = lista_espacios.begin(); it != lista_espacios.end(); it++)
	{
		if ((*it).Get_x1() == E.Get_x1() && (*it).Get_x2() == E.Get_x2() &&
			(*it).Get_y1() == E.Get_y1() && (*it).Get_y2() == E.Get_y2() &&
			(*it).Get_z1() == E.Get_z1() && (*it).Get_z2() == E.Get_z2())
		{
			lista_espacios.erase(it);
			break;
		}

	}
	//Primero miro con los que hay ya que
	std::list< SPACE > ::iterator itfin = lista_espacios.end();
	for (it = lista_espacios.begin(); it != lista_espacios.end();)
	{
		//Si se intersectan hacer los espacios
		if (!(C.Get_x2() <= (*it).Get_x1() || C.Get_x1() >= (*it).Get_x2())
			&& !(C.Get_y2() <= (*it).Get_y1() || C.Get_y1() >= (*it).Get_y2())
			&& !(C.Get_z2() <= (*it).Get_z1() || C.Get_z1() >= (*it).Get_z2()))
		{

			ActualizarEspaciosElegidoMov((*it), C, lista_temp, lista_espacios);
			it = lista_espacios.erase(it);
		}
		else
			++it;

	}
	if (m_juntar_spaces == true)
		JuntarSpacesBloques(lista_espacios, lista_temp, C);
	if (quitar_piezas == true)
	{
		if (m_multicontainer == false)
		{
			//Aqui pruebo si puede quitar alguno y es mas rapido
			if (m_eliminar_espacios == true)
			{
				std::list<SPACE> ::iterator itfin1 = lista_espacios.end();
				for (it = lista_espacios.begin(); it != itfin1;)
				{
					if (((m_dimension_menor > min(min((*it).Get_dx(), (*it).Get_dy()), (*it).Get_dz()))
						|| CabeAlguna((*it).Get_dx(), (*it).Get_dy(), (*it).Get_dz()) == false))
					{
						it = lista_espacios.erase(it);

					}
					else
						++it;
				}
			}
		}
		else
		{
			std::list<SPACE> ::iterator itfin2 = lista_espacios.end();
			for (it = lista_espacios.begin(); it != itfin2;)
			{
				if ((m_dimension_menor_x > (*it).Get_dx()) ||
					(m_dimension_menor_y > (*it).Get_dy()) ||
					(m_dimension_menor_z > (*it).Get_dz()) ||
					(m_menor_volumen > (*it).Get_Volumen()))
				{
					it = lista_espacios.erase(it);

				}
				else
					++it;
			}
		}
	}

	//Buscar inclusiones pero solamente con  los nuevos entres ssi
	EliminarInclusionesNuevos(lista_temp);
	//Buscar inclusiones de los nuevos con los antiguos esta función me debería colocar ya las
	//nuevas ordenadas
	//Aqui pruebo si puede quitar alguno y es mas rapido

	EliminarInclusionesListaAntigua(lista_espacios, lista_temp);

	//Esta función incluye los nuevos en la lista 
	//15-09-06 
//	lista_espacios.insert(lista_espacios.begin(),lista_temp.begin(),lista_temp.end());
	ColocarOrdenadosNuevos(lista_espacios, lista_temp);

	if (m_space_arriba == false)
		m_space_arriba = true;
	/*EliminarInclusionesNuevos(lista_espacios);*/
	//	EliminarInclusiones();
	//	}

}

BLOQUE_ARA& CONTAINER::BuscarPiezasBloqueAra(int kblo)
{
	std::set<BLOQUE_ARA*, compareBlocks>::iterator it = std::find_if(m_set_Bloques.begin(), m_set_Bloques.end(), buscar_por_id(kblo));
	return **it;
}
//void print_loc(long64 x0, long64 y0, long64 z0, ofstream& myfile, vector<Box*>& boxes) 
//{
//	if (n_boxes > 1) {
//		if (block1 == NULL) cout << "error" << endl;
//		block1->print_loc(x0, y0, z0, myfile, boxes);
//		block2->print_loc(x0 + x2, y0 + y2, z0 + z2, myfile, boxes);
//
//		//~ cout << "block " << id << ": (" << x0 << "," << y0 << "," << z0 << "); " << 
//		 //~ ": (" << x0+l << "," << y0+w << "," << z0+h << "); " << endl;
//	}
//	else {
//		myfile << nb_boxes.begin()->first->id;
//		myfile << "	(" << x0 << "," << y0 << "," << z0 << ")	" <<
//			"(" << x0 + l << "," << y0 + w << "," << z0 + h << ")" << endl;
//		boxes.push_back(new Box(x0, y0, z0, x0 + l, y0 + w, z0 + h));
//		calc += l * w * h;
//	}
//
//
//}
